#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

/*=========================================================================================================*/
												/*Ellipse Algorithms*/
#pragma once
#include <iostream>
#include <math.h>
using namespace std;

struct Point
{
	int x, y;
	Point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
};
int Round(double num)
{
	return (int)(num + 0.5);
}

void Draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
	SetPixel(hdc, xc + x, yc + y, color);
	SetPixel(hdc, xc + x, yc - y, color);
	SetPixel(hdc, xc - x, yc - y, color);
	SetPixel(hdc, xc - x, yc + y, color);
}

void DrawEllipseDirect(HDC hdc, Point pc, Point p2, Point p3, COLORREF rgb)
{
	int  a = abs(pc.x - p2.x);
	int  b = abs(pc.y - p3.y);

	double x = a;
	double y = 0;
	double a2 = a * a;
	double b2 = b * b;
	Draw4Points(hdc, pc.x, pc.y, a, 0, rgb);

	while ((b2 * x) > (a2 * y)){	// slope > 1
		y++;
		x = sqrt((double)(a2 * (1 - ((y * y) / (b2)))));
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}
	x = 0;
	y = b;
	while ((b2 * x) < (a2 * y))		// slope < 1
	{
		x++;
		y = sqrt((double)(b2 * (1 - ((x * x) / (a2)))));
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}

}

void DrawEllipsePolar(HDC hdc, Point pc, Point p2, Point p3, COLORREF rgb)
{
	int  a = abs(pc.x - p2.x);
	int  b = abs(pc.y - p3.y);

	double x = a;
	double y = 0;
	double theta = 0;
	double dtheta = 0.001;
	while (theta <= 1.5708)
	{
		x = a * cos(theta);
		y = b * sin(theta);
		theta += dtheta;
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}
}

void DrawEllipsePolarIterative(HDC hdc, Point pc, Point p2, Point p3, COLORREF rgb)
{
	int  a = abs(pc.x - p2.x);
	int  b = abs(pc.y - p3.y);

	double x = a;
	double y = 0;
	double dtheta = 0.0001;
	double cd = cos(dtheta), sd = sin(dtheta);
	Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	while (x >= 0)
	{
		double x1 = x * cd - (a * y * sd) / b;
		y = y * cd + (b * x * sd) / a;
		x = x1;
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}
}

void DrawEllipseMidPoint(HDC hdc, Point pc, Point p2, Point p3, COLORREF rgb)
{
	int  a = abs(pc.x - p2.x);
	int  b = abs(pc.y - p3.y);

	double y = b, x = 0, a2 = a * a, b2 = b * b;
	double d = b2 - a2 * b + 0.25 * a2;
	Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	while (b2 * x <= a2 * y)
	{
		x++;
		if (d > 0)
		{
			y--;
			d += b2 * (2 * x + 3) + a2 * (-2 * y + 2);
		}
		else
		{
			d += b2 * (2 * x + 3);
		}
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}
	d = (x + 0.5) * (x + 0.5) * b2 + a2 * (y - 1) * (y - 1) - a2 * b2;
	Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	while (y != 0)
	{
		y--;
		if (d > 0)
		{
			d += a2 * (-2 * y + 3);
		}
		else
		{
			x++;
			d += b2 * (2 * x + 2) + a2 * (-2 * y + 3);
		}
		Draw4Points(hdc, pc.x, pc.y, Round(x), Round(y), rgb);
	}
}

#endif // ELLIPSE_H_INCLUDED
