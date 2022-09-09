#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <random>

using namespace std;

class Image
{
public:
    Image(std::string name) : width(800), height(800), name(name)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height * 3; j++)
            {
                imageData[i][j] = 0;
            }
        }
    }
    void output()
    {
        // Create and open a text file
        ofstream out(this->name);

        // Write header to file
        out << "P3 " << this->width << " " << this->height << " 255\r\n";

        // Write data
        for (int i = 0; i < this->width; i++)
        {
            for (int j = 0; j < this->height * 3; j++)
            {
                out << this->imageData[i][j] << " ";
            }
            out << "\n";
        }

        // Close the file
        out.close();
    }
    void write(int x, int y, int r, int g, int b)
    {
        if (x < 0 || y < 0 || x >= this->width || y >= this->height)
        {
            return;
        }

        this->imageData[y][x * 3 + 0] = r;
        this->imageData[y][x * 3 + 1] = g;
        this->imageData[y][x * 3 + 2] = b;
    }

private:
    int width;
    int height;
    std::string name;
    unsigned int imageData[800][800 * 3];
};

class Line
{
public:
    Line(int x1, int y1, int x2, int y2) : x1(x1), x2(x2), y1(y1), y2(y2)
    {
    }
    void draw(Image *image, int r, int g, int b)
    {
        int delta_x = this->x2 - this->x1;
        int delta_y = this->y2 - this->y1;

        if (delta_x * delta_x > delta_y * delta_y)
        {
            if (delta_x < 0)
            {
                this->major_x(image, r, g, b, this->x2, this->y2, this->x1, this->y1);
            }
            else
            {
                this->major_x(image, r, g, b, this->x1, this->y1, this->x2, this->y2);
            }
        }
        else
        {
            if (delta_y < 0)
            {
                this->major_y(image, r, g, b, this->x2, this->y2, this->x1, this->y1);
            }
            else
            {
                this->major_y(image, r, g, b, this->x1, this->y1, this->x2, this->y2);
            }
        }
    }
    void calc_midpoint(double *x, double *y)
    {
        *x = (double)(this->x1 + this->x2) / 2;
        *y = (double)(this->y1 + this->y2) / 2;
    }
    double calc_length()
    {
        return sqrt((double)((this->x2 - this->x1) * (this->x2 - this->x1)) + (double)((this->y2 - this->y1) * (this->y2 - this->y1)));
    }
    double calc_slope()
    {
        return (double)(this->y2 - this->y1) / (double)(this->x2 - this->x1);
    }

    int x1_pos()
    {
        return this->x1;
    }
    int y1_pos()
    {
        return this->y1;
    }
    int x2_pos()
    {
        return this->x2;
    }
    int y2_pos()
    {
        return this->y2;
    }

private:
    int x1, x2, y1, y2;

    void major_x(Image *image, int r, int g, int b, int x1, int y1, int x2, int y2)
    {
        int delta_x = x2 - x1;
        int delta_y = y2 - y1;
        int dir = 1;
        if (delta_y < 0)
        {
            dir = -1;
            delta_y = -delta_y;
        }
        int error = delta_y - delta_x;
        int y = y1;

        for (int x = x1; x < x2; x++)
        {
            image->write(x, y, r, g, b);

            if (error >= 0)
            {
                y += dir;
                error -= delta_x;
            }

            error += delta_y;
        }
    }
    void major_y(Image *image, int r, int g, int b, int x1, int y1, int x2, int y2)
    {
        int delta_x = x2 - x1;
        int delta_y = y2 - y1;
        int dir = 1;
        if (delta_x < 0)
        {
            dir = -1;
            delta_x = -delta_x;
        }

        int error = delta_x - delta_y;
        int x = x1;

        for (int y = y1; y < y2; y++)
        {
            image->write(x, y, r, g, b);

            if (error >= 0)
            {
                x += dir;
                error -= delta_y;
            }

            error += delta_x;
        }
    }
};

class Circle
{
public:
    Circle(int x, int y, int r) : x(x), y(y), r(r)
    {
    }
    void draw(Image *image, int r, int g, int b)
    {
        int x, y, y2, y2_new, ty;
        x = 0;
        y = this->r;
        y2 = y * y;
        y2_new = y2;
        ty = (2 * y) - 1;

        while (x <= y)
        {
            if ((y2 - y2_new) >= ty)
            {
                y2 -= ty;
                y -= 1;
                ty -= 2;
            }
            image->write(this->x + x, this->y + y, r, g, b);
            image->write(this->x + x, this->y - y, r, g, b);
            image->write(this->x - x, this->y + y, r, g, b);
            image->write(this->x - x, this->y - y, r, g, b);
            image->write(this->x + y, this->y + x, r, g, b);
            image->write(this->x + y, this->y - x, r, g, b);
            image->write(this->x - y, this->y + x, r, g, b);
            image->write(this->x - y, this->y - x, r, g, b);
            y2_new -= (2 * x) - 3;
            x += 1;
        }
    }
    int radius()
    {
        return this->r;
    }
    int x_pos()
    {
        return this->x;
    }
    int y_pos()
    {
        return this->y;
    }

private:
    int x, y, r;
};

class Triangle
{
public:
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : l1(x1, y1, x2, y2), l2(x2, y2, x3, y3), l3(x3, y3, x1, y1)
    {
    }
    void draw(Image *image, int r, int g, int b)
    {
        this->l1.draw(image, r, g, b);
        this->l2.draw(image, r, g, b);
        this->l3.draw(image, r, g, b);
    }
    void calc_circumcircle(double *x, double *y, double *r)
    {
        double x1, x2, y1, y2, s1, s2;
        s1 = -1 / this->l1.calc_slope();
        s2 = -1 / this->l2.calc_slope();
        this->l1.calc_midpoint(&x1, &y1);
        this->l2.calc_midpoint(&x2, &y2);

        *x = (s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2);
        *y = s1 * (*x - x1) + y1;
        *r = sqrt((*x - this->l1.x1_pos()) * (*x - this->l1.x1_pos()) + (*y - this->l1.y1_pos()) * (*y - this->l1.y1_pos()));
    }
    void calc_orthocenter(double *x, double *y)
    {
        double s1, s2, x1, x2, y1, y2;
        s1 = -1 / this->l1.calc_slope();
        s2 = -1 / this->l2.calc_slope();
        x1 = (double)this->l3.x1_pos();
        x2 = (double)this->l1.x1_pos();
        y1 = (double)this->l3.y1_pos();
        y2 = (double)this->l1.y1_pos();

        *x = (s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2);
        *y = s1 * ((double)(*x) - x1) + y1;
    }
    void calc_incircle(double *x, double *y, double *r)
    {
        double a, b, c, p, p2, area;
        a = this->l1.calc_length();
        b = this->l2.calc_length();
        c = this->l3.calc_length();
        p = a + b + c;
        p2 = p / 2;
        area = sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));

        double ax, ay, bx, by, cx, cy;
        ax = (double)this->l3.x1_pos();
        ay = (double)this->l3.y1_pos();
        bx = (double)this->l1.x1_pos();
        by = (double)this->l1.y1_pos();
        cx = (double)this->l2.x1_pos();
        cy = (double)this->l2.y1_pos();

        *x = (a * ax + b * bx + c * cx) / p;
        *y = (a * ay + b * by + c * cy) / p;
        *r = (area / p2) - 2; // Sub 2 to make it appear inside triangle
    }
    void calc_centroid(double *x, double *y)
    {
        double x1, x2, x3, y1, y2, y3;
        this->l1.calc_midpoint(&x1, &y1);
        this->l2.calc_midpoint(&x2, &y2);
        this->l3.calc_midpoint(&x3, &y3);
        *x = (x1 + x2 + x3) / 3;
        *y = (y1 + y2 + y3) / 3;
    }

private:
    Line l1, l2, l3;
};

/// Returns y3
int extend_line(double x1, double y1, double x2, double y2, double x3)
{
    double slope = (y2 - y1) / (x2 - x1);
    int y3 = slope * (x3 - x1) + y1;
    return y3;
}

int main()
{
    // Make image
    Image *image = new Image("output.ppm");

    // Generate random numbers
    random_device os_seed;
    auto seed = os_seed();

    mt19937 generator(seed);
    uniform_int_distribution<unsigned int> distribute_xy(0, 799);

    auto p1x = distribute_xy(generator);
    auto p1y = distribute_xy(generator);
    auto p2x = distribute_xy(generator);
    auto p2y = distribute_xy(generator);
    auto p3x = distribute_xy(generator);
    auto p3y = distribute_xy(generator);

    //     auto p1x = 200;
    //     auto p1y = 400;
    //     auto p2x = 600;
    //     auto p2y = 401;
    //     auto p3x = 500;
    //     auto p3y = 405;

    // Make triangle
    cout << "Triangle Points: " << p1x << " " << p1y << ", " << p2x << " " << p2y << ", " << p3x << " " << p3y << endl;
    Triangle triangle(p1x, p1y, p2x, p2y, p3x, p3y);
    triangle.draw(image, 255, 98, 179);

    // Make circumcircle
    double x, y, r;
    triangle.calc_circumcircle(&x, &y, &r);
    Circle circumcircle((int)x, (int)y, (int)r);
    circumcircle.draw(image, 0, 255, 0);

    // Draw 9 point circle
    double cx, cy;
    triangle.calc_orthocenter(&cx, &cy);
    x = (x + cx) / 2;
    y = (y + cy) / 2;
    r /= 2;
    Circle ninepoint((int)x, (int)y, (int)r);
    ninepoint.draw(image, 255, 174, 98);

    // Draw euler line
    double ey1, ey2;
    triangle.calc_centroid(&cx, &cy);
    ey1 = extend_line(x, y, cx, cy, 0);
    ey2 = extend_line(x, y, cx, cy, 800);
    Line euler(0, (int)ey1, 800, (int)ey2);
    euler.draw(image, 100, 200, 200);

    // Make incircle
    triangle.calc_incircle(&x, &y, &r);
    Circle incircle(x, y, r);
    incircle.draw(image, 255, 253, 98);

    // Output final image
    image->output();
    delete image;

    return 0;
}