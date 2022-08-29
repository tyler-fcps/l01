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
    cout << "This is my first C++ project!" << endl;

    auto width = 800;
    auto height = 800;

    image::Image *image = new image::Image(width, height, "output.ppm");
    image->print();

    std::random_device os_seed;
    auto seed = os_seed();

    std::mt19937 generator(seed);
    std::uniform_int_distribution<unsigned int> distribute_xy(0, 799);
    std::uniform_int_distribution<unsigned int> distribute_r(50, 100);

    for (int i = 0; i < 100; i++)
    {
        int x = distribute_xy(generator);
        int y = distribute_xy(generator);
        int r = distribute_r(generator);
        shapes::Circle circle = shapes::Circle(x, y, r);
        circle.draw(image, 200, 150, 150);
    }

    image->output();

    return 0;
}