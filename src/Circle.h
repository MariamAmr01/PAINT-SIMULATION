#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
/*=========================================================================================================*/
												/*Circle Algorithms*/
#pragma once
#include <iostream>
#include <math.h>
#include <wtypes.h>

using namespace std;

void Draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc + y, yc - x, c);
    SetPixel(hdc, xc - y, yc - x, c);
    SetPixel(hdc, xc - y, yc + x, c);
}

void DrawCircleDirect(HDC hdc, Point pc, Point p2, COLORREF rgb)
{
    int r = sqrt((pc.x - p2.x) * (pc.x - p2.x) + (pc.y - p2.y) * (pc.y - p2.y));
    int x = r;
    int y = 0;
    int R2 = r * r;
    Draw8Points(hdc, pc.x, pc.y, x, y, rgb);
    while (x > y)
    {
        y++;
        x = Round(sqrt((double)(R2 - y * y)));
        Draw8Points(hdc, pc.x, pc.y, x, y, rgb);

    }
}
void DrawCirclePolar(HDC hdc, int xc, int yc, int R, COLORREF c) {
    double x = R, y = 0, theta = 0;
    Draw8Points(hdc, xc, yc, R, 0, c);
    while (x > y) {
        theta += (1.0 / R);
        x = R * cos(theta);
        y = R * sin(theta);
        Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void DrawCircleIterativePolar(HDC hdc, int xc, int yc, int R, COLORREF c) {
    double x = R, y = 0;
    double dtheta = 1.0 / R;
    double cd = cos(dtheta), sd = sin(dtheta);
    Draw8Points(hdc, xc, yc, R, 0, c);
    while (x > y) {
        double x1 = x * cd - y * sd;
        y = x * sd + y * cd;
        x = x1;
        Draw8Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void DrawCircleMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {   ///??
    int x = 0, y = R;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        double d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - R * R;
        if (d < 0) {
            x++;
        }
        else {
            x++;
            y--;
        }
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}

void DrawCircleModifiedMidpoint(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = 0, y = R;
    int d = 1 - R;
    int d1 = 3;
    int d2 = 5 - 2 * R;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += d1;
            d2 += 2;
            d1 += 2;
            x++;
        }

        else {
            d += d2;
            d2 += 4;
            d1 += 2;
            x++;
            y--;
        }
        Draw8Points(hdc, xc, yc, x, y, c);
    }
}


void DrawBresenhamCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {  ///??
    int x = 0;
    int y = r;
    int d = 1 - r;
    int d1 = 3;
    int d2 = 5 - 2 * r;
    Draw8Points(hdc, xc, yc, x, y, c);
    while (x < y) {
        if (d <= 0) {
            d += d1;
            d2 += 2;
        }
        else {
            d += d2;
            d2 += 4;
            y--;
        }
        d1 += 2;
        x++;

        Draw8Points(hdc, xc, yc, x, y, c);
    }
}


#endif // CIRCLE_H_INCLUDED
