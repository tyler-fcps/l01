#include <vector>
#include <string>
#include "shapes.h"

using namespace std;
using namespace shapes;

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    Line line(x1, y1, x2, y2);
    Triangle::l1 = line;
    Line line(x2, y2, x3, y3);
    Triangle::l2 = line;
    Line line(x1, y1, x3, y3);
    Triangle::l3 = line;
}

void Triangle::draw(image::Image* image, int r, int g, int b) {
    this->l1.draw(image, r, g, b);
    this->l2.draw(image, r, g, b);
    this->l3.draw(image, r, g, b);
}