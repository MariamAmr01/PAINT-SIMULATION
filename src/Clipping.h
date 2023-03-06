#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED
/*=========================================================================================================*/
										/*Clipping Algorithms*/
#include <iostream>
#include <vector>
#include "Curves.h"
#include "Line.h"
#include "Circle.h"
using namespace std;

typedef vector<Point> PointList;
typedef bool (*IsInFunc)(Point& v, int edge);
typedef Point(*IntersectFunc)(Point& v1, Point& v2, int edge);

//outcode for line clipping
struct OutCode { unsigned left : 1, top : 1, right : 1, bottom : 1, all : 1; };

bool InLeft(Point& v, int edge){
    return v.x >= edge;
}
bool InRight(Point& v, int edge)
{
    return v.x <= edge;
}
bool InTop(Point& v, int edge)
{
    return v.y >= edge;
}
bool InBottom(Point& v, int edge)
{
    return v.y <= edge;
}

Point VIntersect(Point& v1, Point& v2, int xedge)
{
    Point res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
Point HIntersect(Point& v1, Point& v2, int yedge)
{
    Point res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}

int getLength(int x1, int y1, int x2, int y2) {
    return Round(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

OutCode GetOutCode(double x, double y, int xleft, int ytop, int xright, int ybottom)
{
    OutCode out;
    out.all = 0, out.left = 0, out.top = 0, out.right = 0, out.bottom = 0;
    if (x < xleft)out.left = 1; else if (x > xright)out.right = 1;
    if (y < ytop)out.top = 1; else if (y > ybottom)out.bottom = 1;
    if (out.left || out.right || out.top || out.bottom)
    {
        out.all = 1;
    }
    return out;
}

//get intersection
void VIntersect(double xs, double ys, double xe, double ye, int x, double* xi, double* yi)
{
    *xi = x;
    *yi = ys + (x - xs) * (ye - ys) / (xe - xs);
}
void HIntersect(double xs, double ys, double xe, double ye, int y, double* xi, double* yi)
{
    *yi = y;
    *xi = xs + (y - ys) * (xe - xs) / (ye - ys);
}

//Rec line clipping
void RecCohenSuth(HDC hdc, int xs, int ys, int xe, int ye, int xleft, int ytop, int xright, int ybottom, COLORREF color)
{
    double x1 = xs, y1 = ys, x2 = xe, y2 = ye;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
    while ((out1.all || out2.all))
    {
        double xi, yi;
        if (out1.left && out2.left || out1.right && out2.right || out1.top && out2.top || out1.bottom && out2.bottom)
        {
            break;
        }
        if (out1.all)
        {
            if (out1.left)VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out1.top)HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out1.right)VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
        }
        else
        {
            if (out2.left)VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out2.top)HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out2.right)VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
        }
    }
    if (!out1.all && !out2.all)
    {
        DrawLineDDA(hdc, Round(x1), Round(y1), Round(x2), Round(y2), color);
    }
}
//Rec polygon clipping
PointList ClipWithEdge(PointList p, int edge, IsInFunc In, IntersectFunc Intersect)
{
    PointList OutList;
    Point v1 = p[p.size() - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < (int)p.size(); i++)
    {
        Point v2 = p[i];
        bool v2_in = In(v2, edge);
        if (!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
            OutList.push_back(v2);
        }
        else if (v1_in && v2_in) OutList.push_back(v2);
        else if (v1_in) OutList.push_back(Intersect(v1, v2, edge));
        v1 = v2;
        v1_in = v2_in;
    }
    return OutList;
}
void RecPolygonClip(HDC hdc, vector<Point> p, int xleft, int ytop, int xright, int ybottom,COLORREF color)
{
    PointList vlist;
    for (int i = 0; i < p.size(); i++)vlist.push_back(Point(p[i].x, p[i].y));
    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
    Point v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); i++)
    {
        Point v2 = vlist[i];
        DrawLineDDA(hdc, Round(v1.x), Round(v1.y), Round(v2.x), Round(v2.y), color);
        v1 = v2;
    }
}
//Rec point clipping
void RecPointClipping(HDC hdc, int x, int y, int xleft, int ytop, int xright, int ybottom, COLORREF color)
{

    if (x >= xleft && x <= xright && y >= ytop && y <= ybottom)
        SetPixel(hdc, x, y, color);
}

void DrawSquare(HDC hdc, int xleft, int ytop, int length) {
    DrawLineDDA(hdc, xleft, ytop, xleft, ytop+length, RGB(0, 0, 0));
    DrawLineDDA(hdc, xleft, ytop, xleft+length, ytop, RGB(0, 0, 0));
    DrawLineDDA(hdc, xleft+length, ytop, xleft+length, ytop+length, RGB(0, 0, 0));
    DrawLineDDA(hdc, xleft, ytop+length, xleft+length, ytop+length, RGB(0, 0, 0));
}

//Square line clipping
void SquareCohenSuth(HDC hdc, int xs, int ys, int xe, int ye, int xleft, int ytop, int length,COLORREF color)
{
    double x1 = xs, y1 = ys, x2 = xe, y2 = ye;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xleft + length, ytop + length);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xleft + length, ytop + length);
    while ((out1.all || out2.all))
    {
        double xi, yi;
        if (out1.left && out2.left || out1.right && out2.right || out1.top && out2.top || out1.bottom && out2.bottom)
        {
            break;
        }
        if (out1.all)
        {
            if (out1.left)VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out1.top)HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out1.right)VIntersect(x1, y1, x2, y2, xleft + length, &xi, &yi);
            else HIntersect(x1, y1, x2, y2, ytop + length, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xleft + length, ytop + length);
        }
        else
        {
            if (out2.left)VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out2.top)HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out2.right)VIntersect(x1, y1, x2, y2, xleft + length, &xi, &yi);
            else HIntersect(x1, y1, x2, y2, ytop + length, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xleft + length, ytop + length);
        }
    }
    if (!out1.all && !out2.all)
    {
        DrawLineDDA(hdc, Round(x1), Round(y1), Round(x2), Round(y2), color);
    }
}

//Square point clipping
void SquarePointClipping(HDC hdc, int x, int y, int xleft, int ytop, int length, COLORREF color)
{
    if (x >= xleft && x <= xleft + length && y >= ytop && y <= ytop + length)
        SetPixel(hdc, x, y, color);
}
//Circle Point Clipping
void CirclePointClipping(HDC hdc, int x, int y, int centerX, int centerY, int radius, COLORREF color)
{
    if (getLength(x, y, centerX, centerY) < radius)
        SetPixel(hdc, x, y, color);
}
//Circle Line Clipping
void CircleLineClipping(HDC hdc, int x1, int y1, int x2, int y2, int centerX, int centerY, int radius, COLORREF c) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int length;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)swap(x1, y1, x2, y2);
        length = getLength(x1, y1, centerX, centerY);
        if (length < radius)
        {
            SetPixel(hdc, x1, y1, c);
        }
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1) * dy / dx;
            length = getLength(x, Round(y), centerX, centerY);
            if (length < radius)
            {
                SetPixel(hdc, x, Round(y), c);
            }
        }
    }
    else {
        if (y1 > y2)swap(x1, y1, x2, y2);
        length = getLength(x1, y1, centerX, centerY);
        if (length < radius)
        {
            SetPixel(hdc, x1, y1, c);
        }
        int y = y1;
        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1) * dx / dy;
            length = getLength(Round(x), y, centerX, centerY);
            if (length < radius)
            {
                SetPixel(hdc, Round(x), y, c);
            }
        }
    }
}


#endif // CLIPPING_H_INCLUDED
