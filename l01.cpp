#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"
#include "shapes.h"
#include <cctype>
#include <random>

using namespace std;

int main()
{
    // Make image
    auto width = 800;
    auto height = 800;
    image::Image *image = new image::Image(width, height, "output.ppm");
    image->print();

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
    cout << p1x << " " << p1y << " " << p2x << " " << p2y << " " << p3x << " " << p3y << endl;
    shapes::Triangle triangle(p1x, p1y, p2x, p2y, p3x, p3y);
    triangle.draw(image, 255, 0, 0);

    // Make circumcircle
    int x, y, r;
    triangle.calc_circumcircle(&x, &y, &r);
    shapes::Circle circumcircle(x, y, r);
    circumcircle.draw();
    
    // Output final image
    image->output();

    return 0;
}