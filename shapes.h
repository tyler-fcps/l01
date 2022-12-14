#pragma once
#include "image.h"

namespace shapes
{
    class Line
    {
    public:
        Line() {}
        Line(int x1, int y1, int x2, int y2);
        void draw(image::Image *, int r, int g, int b);
        void calc_midpoint(double *x, double *y);
        double calc_length();
        double calc_slope();

        int x1_pos()
        {
            return this->x1;
        }
        int y1_pos()
        {
            return this->y1;
        }
        int x2_pos()
        {
            return this->x2;
        }
        int y2_pos()
        {
            return this->y2;
        }

    private:
        int x1, x2, y1, y2;

        void major_x(image::Image *, int r, int g, int b);
        void major_y(image::Image *, int r, int g, int b);
    };

    class Circle
    {
    public:
        Circle(int x, int y, int r);
        void draw(image::Image *, int r, int g, int b);
        int radius()
        {
            return this->r;
        }
        int x_pos()
        {
            return this->x;
        }
        int y_pos()
        {
            return this->y;
        }

    private:
        int x, y, r;
    };

    class Triangle
    {
    public:
        Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
        void draw(image::Image *, int r, int g, int b);
        void calc_circumcircle(double *x, double *y, double *r);
        void calc_orthocenter(double *x, double *y);
        void calc_incircle(double *x, double *y, double *r);
        void calc_centroid(double *x, double *y);

    private:
        Line l1, l2, l3;
    };
}