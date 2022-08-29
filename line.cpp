#include <vector>
#include <string>
#include "shapes.h"

using namespace std;
using namespace shapes;

Line::Line(int x1, int y1, int x2, int y2)
{
    if (x2 > x1)
    {
        Line::x1 = x1;
        Line::x2 = x2;
        Line::y1 = y1;
        Line::y2 = y2;
    }
    else
    {
        Line::x1 = x2;
        Line::x2 = x1;
        Line::y1 = y2;
        Line::y2 = y1;
    }
}

void Line::draw(image::Image *image, int r, int g, int b)
{
    int delta_x = this->x2 - this->x1;
    int delta_y = this->y2 - this->y1;
    if (delta_x > delta_y)
    {
        this->major_x(image, r, g, b);
    }
    else
    {
        this->major_y(image, r, g, b);
    }
}

void Line::major_x(image::Image *image, int r, int g, int b)
{
    int delta_x = this->x2 - this->x1;
    int delta_y = this->y2 - this->y1;
    int dir = 1;
    if (delta_y < 0)
    {
        dir = -1;
        delta_y = -delta_y;
    }
    int error = delta_y - delta_x;
    int y = this->y1;

    for (int x = this->x1; x < this->x2; x++)
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

void Line::major_y(image::Image *image, int r, int g, int b)
{
    int delta_x = this->x2 - this->x1;
    int delta_y = this->y2 - this->y1;
    int dir = 1;
    if (delta_x < 0)
    {
        dir = -1;
        delta_x = -delta_x;
    }
    int error = delta_x - delta_y;
    int x = this->x1;

    for (int y = this->y1; y < this->y2; y++)
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