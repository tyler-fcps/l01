#include <vector>
#include <string>
#include <math.h>
#include "shapes.h"

using namespace std;
using namespace shapes;

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : l1(x1, y1, x2, y2), l2(x2, y2, x3, y3), l3(x3, y3, x1, y1)
{
}

void Triangle::calc_centroid(double *x, double *y)
{
    double x1, x2, x3, y1, y2, y3;
    this->l1.calc_midpoint(&x1, &y1);
    this->l2.calc_midpoint(&x2, &y2);
    this->l3.calc_midpoint(&x3, &y3);
    *x = (x1 + x2 + x3) / 3;
    *y = (y1 + y2 + y3) / 3;
}

void Triangle::calc_incircle(double *x, double *y, double *r)
{
    double a, b, c, p, p2, area;
    a = this->l1.calc_length();
    b = this->l2.calc_length();
    c = this->l3.calc_length();
    p = a + b + c;
    p2 = p / 2;
    area = sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));

    double ax, ay, bx, by, cx, cy;
    ax = (double)this->l3.x1_pos();
    ay = (double)this->l3.y1_pos();
    bx = (double)this->l1.x1_pos();
    by = (double)this->l1.y1_pos();
    cx = (double)this->l2.x1_pos();
    cy = (double)this->l2.y1_pos();

    *x = (a * ax + b * bx + c * cx) / p;
    *y = (a * ay + b * by + c * cy) / p;
    *r = (area / p2) - 2; // Sub 2 to make it appear inside triangle
}

void Triangle::calc_orthocenter(double *x, double *y)
{
    double s1, s2, x1, x2, y1, y2;
    s1 = -1 / this->l1.calc_slope();
    s2 = -1 / this->l2.calc_slope();
    x1 = (double)this->l3.x1_pos();
    x2 = (double)this->l1.x1_pos();
    y1 = (double)this->l3.y1_pos();
    y2 = (double)this->l1.y1_pos();

    *x = (s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2);
    *y = s1 * ((double)(*x) - x1) + y1;
}

void Triangle::calc_circumcircle(double *x, double *y, double *r)
{
    double x1, x2, y1, y2, s1, s2;
    s1 = -1 / this->l1.calc_slope();
    s2 = -1 / this->l2.calc_slope();
    this->l1.calc_midpoint(&x1, &y1);
    this->l2.calc_midpoint(&x2, &y2);

    *x = (s1 * x1 - s2 * x2 + y2 - y1) / (s1 - s2);
    *y = s1 * (*x - x1) + y1;
    *r = sqrt((*x - this->l1.x1_pos()) * (*x - this->l1.x1_pos()) + (*y - this->l1.y1_pos()) * (*y - this->l1.y1_pos()));
}

void Triangle::draw(image::Image *image, int r, int g, int b)
{
    this->l1.draw(image, r, g, b);
    this->l2.draw(image, r, g, b);
    this->l3.draw(image, r, g, b);
}