#include <vector>
#include <string>
#include <math.h>
#include "shapes.h"

using namespace std;
using namespace shapes;

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : l1(x1, y1, x2, y2), l2(x2, y2, x3, y3), l3(x3, y3, x1, y1)
{
}

void Triangle::calc_centroid(int* x, int* y) {
    int x1, x2, x3, y1, y2, y3;
    this->l1.calc_midpoint(&x1, &y1);
    this->l2.calc_midpoint(&x2, &y2);
    this->l3.calc_midpoint(&x3, &y3);
    *x = (x1 + x2 + x3) / 3;
    *y = (y1 + y2 + y3) / 3;
}

void Triangle::calc_circumcircle(int* x, int* y, int* r) {
    int x1i, x2i, y1i, y2i;
    double s1 = this->l1.calc_slope();
    double s2 = this->l2.calc_slope();
    this->l1.calc_midpoint(&x1i, &y1i);
    this->l2.calc_midpoint(&x2i, &y2i);
    double x1, x2, y1, y2;
    x1 = (double)x1i;
    x2 = (double)x2i;
    y1 = (double)y1i;
    y2 = (double)y2i;

    *x = (int)((s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2));
    *y = (int)(s1 * ((double)(*x) - x1) + y1);
    *r = (int)(sqrt(((double)(*x) - this->l1.x1_pos()) * ((double)(*x) - this->l1.x1_pos()) + ((double)(*y) - this->l1.y1_pos()) * ((double)(*y) - this->l1.y1_pos())));
}

void Triangle::draw(image::Image* image, int r, int g, int b) {
    this->l1.draw(image, r, g, b);
    this->l2.draw(image, r, g, b);
    this->l3.draw(image, r, g, b);
}