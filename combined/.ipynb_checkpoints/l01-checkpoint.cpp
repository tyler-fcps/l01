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
    int get_width() {
        return this->width;
    }
    int get_height() {
        return this->height;
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
    Line(double x1, double y1, double x2, double y2) : x1(x1), x2(x2), y1(y1), y2(y2)
    {
    }
    void draw(Image *image, int r, int g, int b)
    {
        double delta_x = this->x2 - this->x1;
        double delta_y = this->y2 - this->y1;

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
        *x = (this->x1 + this->x2) / 2;
        *y = (this->y1 + this->y2) / 2;
    }
    double calc_length()
    {
        return sqrt((this->x2 - this->x1) * (this->x2 - this->x1) + (this->y2 - this->y1) * (this->y2 - this->y1));
    }
    double calc_slope()
    {
        return (this->y2 - this->y1) / (this->x2 - this->x1);
    }

    double x1_pos()
    {
        return this->x1;
    }
    double y1_pos()
    {
        return this->y1;
    }
    double x2_pos()
    {
        return this->x2;
    }
    double y2_pos()
    {
        return this->y2;
    }

private:
    double x1, x2, y1, y2;

    void major_x(Image *image, int r, int g, int b, double x1d, double y1d, double x2d, double y2d)
    {
        double width, height;
        width = (double)image->get_width();
        height = (double)image->get_height();
        int x1, y1, x2, y2;
        x1 = (int)(width * x1d);
        y1 = (int)(height * y1d);
        x2 = (int)(width * x2d);
        y2 = (int)(height * y2d);
        
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
    void major_y(Image *image, int r, int g, int b, double x1d, double y1d, double x2d, double y2d)
    {
        double width, height;
        width = (double)image->get_width();
        height = (double)image->get_height();
        int x1, y1, x2, y2;
        x1 = (int)(width * x1d);
        y1 = (int)(height * y1d);
        x2 = (int)(width * x2d);
        y2 = (int)(height * y2d);
        
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
    Circle(double x, double y, double r) : x(x), y(y), r(r)
    {
    }
    void draw(Image *image, int r, int g, int b)
    {
        int x, y, y2, y2_new, ty, xoff, yoff;
        x = 0;
        y = (int)(this->r * (double)image->get_width());
        y2 = y * y;
        y2_new = y2;
        ty = (2 * y) - 1;
        xoff = (this->x * (double)image->get_width());
        yoff = (this->y * (double)image->get_height());
        
        cout << y << " " << xoff << " " << yoff << " " << this->r << endl;

        while (x <= y)
        {
            if ((y2 - y2_new) >= ty)
            {
                y2 -= ty;
                y -= 1;
                ty -= 2;
            }
            image->write(xoff + x, yoff + y, r, g, b);
            image->write(xoff + x, yoff - y, r, g, b);
            image->write(xoff - x, yoff + y, r, g, b);
            image->write(xoff - x, yoff - y, r, g, b);
            image->write(xoff + y, yoff + x, r, g, b);
            image->write(xoff + y, yoff - x, r, g, b);
            image->write(xoff - y, yoff + x, r, g, b);
            image->write(xoff - y, yoff - x, r, g, b);
            y2_new -= (2 * x) - 3;
            x += 1;
        }
    }
    double radius()
    {
        return this->r;
    }
    double x_pos()
    {
        return this->x;
    }
    double y_pos()
    {
        return this->y;
    }

private:
    double x, y, r;
};

class Triangle
{
public:
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3) : l1(x1, y1, x2, y2), l2(x2, y2, x3, y3), l3(x3, y3, x1, y1)
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
        x1 = this->l3.x1_pos();
        x2 = this->l1.x1_pos();
        y1 = this->l3.y1_pos();
        y2 = this->l1.y1_pos();

        *x = (s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2);
        *y = s1 * (*x - x1) + y1;
    }
    void calc_incircle(double *x, double *y, double *r)
    {
        double a, b, c, p, p2, r2;
        a = this->l1.calc_length();
        b = this->l2.calc_length();
        c = this->l3.calc_length();
        p = a + b + c;
        p2 = p / 2;
        r2 = ((p2 - a) * (p2 - b) * (p2 - c)) / p2;

        double ax, ay, bx, by, cx, cy;
        ax = this->l3.x1_pos();
        ay = this->l3.y1_pos();
        bx = this->l1.x1_pos();
        by = this->l1.y1_pos();
        cx = this->l2.x1_pos();
        cy = this->l2.y1_pos();

        *x = (a * ax + b * bx + c * cx) / p;
        *y = (a * ay + b * by + c * cy) / p;
        *r = sqrt(r2);
    }

private:
    Line l1, l2, l3;
};

/// Returns y3
double extend_line(double x1, double y1, double x2, double y2, double x3)
{
    double slope = (y2 - y1) / (x2 - x1);
    double y3 = slope * (x3 - x1) + y1;
    return y3;
}

int main()
{
    // Make image
    Image *image = new Image("output.ppm");

    // Generate random numbers
    random_device os_seed;
    mt19937 generator(os_seed());
    std::uniform_real_distribution<> distribute_xy(0, 1);

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
    Circle circumcircle(x, y, r);
    circumcircle.draw(image, 0, 255, 0);

    // Draw 9 point circle
    double cx, cy;
    triangle.calc_orthocenter(&cx, &cy);
    x = (x + cx) / 2;
    y = (y + cy) / 2;
    r /= 2;
    Circle ninepoint(x, y, r);
    ninepoint.draw(image, 255, 174, 98);

    // Draw euler line
    double ey1, ey2;
    ey1 = extend_line(x, y, cx, cy, 0);
    ey2 = extend_line(x, y, cx, cy, 1);
    Line euler(0, ey1, 1, ey2);
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