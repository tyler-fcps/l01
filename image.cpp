#include <fstream>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;
using namespace image;

Image::Image(string name) : width(800), height(800), name(name)
{
    for (int i = 0; i < width; i++)
    {
        for(int j = 0; j < height * 3; j++) 
        {
            imageData[i][j] = 0;
        }
    }
}

void Image::write(int x, int y, int r, int g, int b)
{
    if (x < 0 || y < 0 || x >= this->width || y >= this->height)
    {
        return;
    }

    this->imageData[x][y * 3 + 0] = r;
    this->imageData[x][y * 3 + 1] = g;
    this->imageData[x][y * 3 + 2] = b;
}

void Image::output()
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