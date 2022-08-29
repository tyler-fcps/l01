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

    auto p1 = distribute_xy(generator);    
    auto p2 = distribute_xy(generator);
    auto p3 = distribute_xy(generator);

    // Make triangle
    
    
    // Output final image
    image->output();

    return 0;
}