#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"
#include "shapes.h"
#include <cctype>
#include <random>

using namespace std;

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
    image::Image image = image::Image("output.ppm");

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
    shapes::Triangle triangle(p1x, p1y, p2x, p2y, p3x, p3y);
    triangle.draw(&image, 255, 98, 179);

    // Make circumcircle
    double x, y, r;
    triangle.calc_circumcircle(&x, &y, &r);
    shapes::Circle circumcircle((int)x, (int)y, (int)r);
    circumcircle.draw(&image, 0, 255, 0);

    // Draw 9 point circle
    double cx, cy;
    triangle.calc_orthocenter(&cx, &cy);
    x = (x + cx) / 2;
    y = (y + cy) / 2;
    r /= 2;
    shapes::Circle ninepoint((int)x, (int)y, (int)r);
    ninepoint.draw(&image, 255, 174, 98);
    
    // Draw euler line
    double ey1, ey2;
    triangle.calc_centroid(&cx, &cy);
    ey1 = extend_line(x, y, cx, cy, 0);
    ey2 = extend_line(x, y, cx, cy, 800);
    shapes::Line euler(0, (int)ey1, 800, (int)ey2);
    euler.draw(&image, 100, 200, 200);

    // Make incircle
    triangle.calc_incircle(&x, &y, &r);
    shapes::Circle incircle(x, y, r);
    incircle.draw(&image, 255, 253, 98);

    // Output final image
    image.output();

    return 0;
}