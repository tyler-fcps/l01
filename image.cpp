#include <fstream>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;
using namespace image;

Image::Image(string name) : width(800), height(800), name(name)
{
    for (int i = 0; i < width * height * 3; i++)
    {
        imageData[i] = 233;
    }
}

void Image::write(int x, int y, int r, int g, int b)
{
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
    {
        return;
    }

    int i = (x + y * this->width) * 3;
    this->imageData[i + 0] = r;
    this->imageData[i + 1] = g;
    this->imageData[i + 2] = b;
}

void Image::output()
{
    // Create and open a text file
    ofstream out(this->name);

    // Write header to file
    out << "P3 " << this->width << " " << this->height << " 255\r\n";

    // Write data
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width * 3; j++)
        {
            out << this->imageData[j + i * this->width * 3] << " ";
        }
        out << "\n";
    }

    // Close the file
    out.close();
}