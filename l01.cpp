#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"
#include "shapes.h"
#include <cctype>
#include <random>

using namespace std;

/// Returns y3
int extend_line(int x1, int y1, int x2, int y2, int x3)
{
    double slope = (double)(y2 - y1) / (double)(x2 - x1);
    int y3 = (int)(slope * (double)(x3 - x1) + (double)y1);
    return y3;
}

int main()
{
    // Make image
    image::Image *image = new image::Image("output.ppm");

    // Generate random numbers
    std::random_device os_seed;
    auto seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<unsigned int> distribute_xy(0, 799);

    auto p1x = distribute_xy(generator);
    auto p1y = distribute_xy(generator);
    auto p2x = distribute_xy(generator);
    auto p2y = distribute_xy(generator);
    auto p3x = distribute_xy(generator);
    auto p3y = distribute_xy(generator);

    // Make triangle
    cout << "Triangle Points: " << p1x << " " << p1y << ", " << p2x << " " << p2y << ", " << p3x << " " << p3y << endl;
    shapes::Triangle triangle(p1x, p1y, p2x, p2y, p3x, p3y);
    triangle.draw(image, 255, 98, 179);

    // Make circumcircle
    int x, y, r;
    triangle.calc_circumcircle(&x, &y, &r);
    shapes::Circle circumcircle(x, y, r);
    circumcircle.draw(image, 0, 255, 0);

    // Draw 9 point circle
    int cx, cy;
    triangle.calc_orthocenter(&cx, &cy);
    shapes::Line oh(cx, cy, x, y);
    oh.calc_midpoint(&x, &y);
    r /= 2;
    shapes::Circle ninepoint(x, y, r);
    ninepoint.draw(image, 255, 174, 98);
    
    // Draw euler line
    int ey1, ey2;
    triangle.calc_centroid(&cx, &cy);
    ey1 = extend_line(x, y, cx, cy, 0);
    ey2 = extend_line(x, y, cx, cy, 800);
    shapes::Line euler(0, ey1, 800, ey2);
    euler.draw(image, 100, 200, 200);

    // Make incircle
    triangle.calc_incircle(&x, &y, &r);
    shapes::Circle incircle(x, y, r);
    incircle.draw(image, 255, 253, 98);

    // Output final image
    image->output();

    return 0;
}