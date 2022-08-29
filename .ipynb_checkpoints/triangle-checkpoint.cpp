#include <vector>
#include <string>
#include "shapes.h"

using namespace std;
using namespace shapes;

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : l1(x1, y1, x2, y2), l2(x2, y2, x3, y3), l3(x3, y3, x1, y1)
{
}

void Triangle::draw(image::Image* image, int r, int g, int b) {
    this->l1.draw(image, r, g, b);
    this->l2.draw(image, r, g, b);
    this->l3.draw(image, r, g, b);
}