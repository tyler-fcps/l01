#include <vector>
#include <string>
#include "shapes.h"

using namespace std;
using namespace shapes;

Circle::Circle(int x, int y, int r) : x(x), y(y), r(r)
{
}

void Circle::draw(image::Image *image, int r, int g, int b)
{
    int x, y, xmax, y2, y2_new, ty;
    xmax = (int)(this->r * 0.70710678); // maximum x at radius/sqrt(2)
    y = this->r;
    y2 = y * y;
    ty = (2 * y) - 1;
    y2_new = y2;
    for (x = 0; x <= xmax + 1; x++)
    {
        if ((y2 - y2_new) >= ty)
        {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }
        image->write(this->x + x, this->y + y, r, g, b);
        image->write(this->x + x, this->y - y, r, g, b);
        image->write(this->x - x, this->y + y, r, g, b);
        image->write(this->x - x, this->y - y, r, g, b);
        image->write(this->x + y, this->y + x, r, g, b);
        image->write(this->x + y, this->y - x, r, g, b);
        image->write(this->x - y, this->y + x, r, g, b);
        image->write(this->x - y, this->y - x, r, g, b);
        y2_new -= (2 * x) - 3;
    }
}