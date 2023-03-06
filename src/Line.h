#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

/*=========================================================================================================*/
												/*Line Algorithms*/
#pragma once
#include <iostream>
#include <math.h>
#include <wtypes.h>
using namespace std;

void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}

void DrawLineParametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    double dx = x2 - x1, dy = y2 - y1, x = 0, y = 0;
    for (double t = 0; t < 1; t += 0.0001) {
        x = x1 + t * (x2 - x1);
        y = y1 + t * (y2 - y1);
        SetPixel(hdc, Round(x), Round(y), c);
    }
}

void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dx) >= abs(dy)) {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        int x = x1;
        double y = y1;
        double m = (double)dy / dx;
        SetPixel(hdc, x1, y1, c);
        while (x < x2) {
            x++;
            y += m;
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        double x = x1;
        int y = y1;
        double m = (double)dx / dy;
        SetPixel(hdc, x1, y1, c);
        while (y < y2) {
            y++;
            x += m;
            SetPixel(hdc, Round(x), y, c);
        }
    }
}

void drawLineMidPoint(HDC hdc, Point p1, Point p2, COLORREF rgb)
{
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int x, y;
    double m = (double)dy / dx;
    if (abs(dx) > abs(dy))
    {
        if (p1.x > p2.x)
        {
            swap(p1.x, p1.y, p2.x, p2.y);
            dx *= -1;
            dy *= -1;
        }
        x = p1.x;
        y = p1.y;
        if (m >= 0 && m <= 1)
        {

            int d = dx - 2 * dy;
            int d1 = 2 * (dx - dy);
            int d2 = -2 * dy;
            SetPixel(hdc, x, y, rgb);
            while (x != p2.x)
            {
                x++;
                if (d < 0)
                {
                    d += d1;
                    y++;
                }
                else
                    d += d2;
                SetPixel(hdc, x, y, rgb);
            }
        }
        else if (-1 <= m && m <= 0)
        {

            int d = -1 * dx - 2 * dy;;
            int d1 = -2 * dx - 2 * dy;
            int d2 = -2 * dy;
            while (x != p2.x)
            {
                x++;
                if (d > 0)
                {
                    y--;
                    d += d1;
                }
                else d += d2;
                SetPixel(hdc, x, y, rgb);
            }
        }
    }
    else
    {
        if (p1.y > p2.y)
        {
            swap(p1.x, p1.y, p2.x, p2.y);
            dx *= -1;
            dy *= -1;
        }
        x = p1.x;
        y = p1.y;
        if (m > 1)
        {
            int d = 2 * dx - dy;
            int d1 = 2 * (dx - dy);
            int d2 = 2 * dx;
            while (y != p2.y)
            {
                y++;
                if (d > 0)
                {
                    d += d1;
                    x++;
                }
                else
                {
                    d += d2;
                }
                SetPixel(hdc, x, y, rgb);
            }
        }
        else if (m <= -1)
        {
            //cout<<"Third Condition"<<endl;
            int d = 2 * dx + dy;
            int d1 = 2 * (dx + dy);
            int d2 = 2 * dx;
            SetPixel(hdc, x, y, rgb);
            while (y != p2.y)
            {
                y++;
                if (d < 0)
                {
                    d += d1;
                    x--;
                }
                else d += d2;
                SetPixel(hdc, x, y, rgb);
            }
        }
    }
}

void drawLineMidPoint1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF rgb)
{
    Point p1, p2;
    p1.x = x1, p2.x = x2, p1.y = y1, p2.y = y2;
    drawLineMidPoint(hdc, p1, p2, rgb);
}

void DrawCartesianLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    double dx = x2 - x1;
    double dy = y2 - y1;

    if (abs(dy) <= abs(dx)) {
        int x;
        double y;
        if (x2 < x1) swap(x1, y1, x2, y2);
        x = x1;
        SetPixel(hdc, x1, y1, c);
        while (x < x2) {
            x++;
            y = y1 + (x - x1) * (dy / dx);
            SetPixel(hdc, x, Round(y), c);
        }
    }
    else {
        double x;
        int y;

        if (y2 < y1) swap(x1, y1, x2, y2);
        y = y1;
        SetPixel(hdc, x1, y1, c);
        while (y < y2) {
            y++;
            x = x1 + (y - y1) * (dx / dy);
            SetPixel(hdc, Round(x), y, c);
        }
    }
}
#endif // LINE_H_INCLUDED
