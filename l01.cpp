#include <iostream>
#include <vector>
#include <fstream>
#include "image.h"

using namespace std;

int main()
{
    cout << "This is my first C++ project!" << endl;

    auto width = 800;
    auto height = 800;

    image::Image *image = new image::Image(width, height, "output.ppm");
    image->print();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image->write(i, j, i % 255, j % 255, 10);
        }
    }

    image->output();

    return 0;
}