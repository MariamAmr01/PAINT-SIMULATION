#ifndef CURVES_H_INCLUDED
#define CURVES_H_INCLUDED
/*=========================================================================================================*/
												/*Curves Algorithms*/
#pragma once
#include <iostream>
#include <math.h>
#include <wtypes.h>
#include "Ellipse.h"
using namespace std;

void DrawHermiteCurve(HDC hdc, Point& p1, Point& T1, Point& p2, Point& T2, COLORREF c) {
    // Alpha --> X
    double a0 = p1.x;
    double a1 = T1.x;
    double a2 = -3 * p1.x - 2 * T1.x + 3 * p2.x - T2.x;
    double a3 = 2 * p1.x + T1.x - 2 * p2.x + T2.x;

    // Beta --> Y
    double b0 = p1.y;
    double b1 = T1.y;
    double b2 = -3 * p1.y - 2 * T1.y + 3 * p2.y - T2.y;
    double b3 = 2 * p1.y + T1.y - 2 * p2.y + T2.y;

    for (double t = 0; t <= 1; t += 0.001) {
        double t2 = t * t;
        double t3 = t2 * t;

        double x = a0 + t * a1 + t2 * a2 + t3 * a3;
        double y = b0 + t * b1 + t2 * b2 + t3 * b3;
        SetPixel(hdc, Round(x), Round(y), c);
    }
}

void DrawCardinalSpline(HDC hdc, vector<Point> P, int n, double c, COLORREF color) {   ///??

    vector<Point> T;
    double factor = (1 - c) / 2;
    T.push_back(*new Point(factor * (P[1].x - P[0].x), factor * (P[1].y - P[0].y)));
    for (int i = 1; i < n - 1; i++)
    {
       T.push_back(*new Point(factor * (P[i + 1].x - P[i - 1].x), factor * (P[i + 1].y - P[i - 1].y)));
    }

    T.push_back(*new Point(factor * (P[n - 1].x - P[n - 2].x), factor * (P[n - 1].y - P[n - 2].y)));

    for (int i = 0; i < n - 1; i++)
    {
        DrawHermiteCurve(hdc, P[i], T[i], P[i + 1], T[i + 1], color);
    }

}

void DrawBezierCurve(HDC hdc, Point& p1, Point& p2, Point& p3, Point& p4, COLORREF c) {
    // Alpha --> X
    double a0 = p1.x;
    double a1 = 3 * p2.x - 3 * p1.x;
    double a2 = 3 * p1.x - 6 * p2.x + 3 * p3.x;
    double a3 = -1 * p1.x + 3 * p2.x - 3 * p3.x + p4.x;

    // Beta --> Y
    double b0 = p1.y;
    double b1 = 3 * p2.y - 3 * p1.y;
    double b2 = 3 * p1.y - 6 * p2.y + 3 * p3.y;
    double b3 = -1 * p1.y + 3 * p2.y - 3 * p3.y + p4.y;

    for (double t = 0; t <= 1; t += 0.001)
    {
        double t2 = t * t;
        double t3 = t2 * t;

        double x = a0 + t * a1 + t2 * a2 + t3 * a3;
        double y = b0 + t * b1 + t2 * b2 + t3 * b3;

        SetPixel(hdc, Round(x), Round(y), c);
    }
}


#endif // CURVES_H_INCLUDED
