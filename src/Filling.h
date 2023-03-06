#ifndef FILLING_H_INCLUDED
#define FILLING_H_INCLUDED
/*=========================================================================================================*/
/*Filling Algorithms*/
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <wtypes.h>
#include "Ellipse.h"
#include "Line.h"
#include "Curves.h"
#include "Circle.h"

#pragma once

void generateLines(HDC hdc, int xc, int yc, int x, int y, COLORREF c, string q) {

    if (q == "1") {
        DrawCartesianLine(hdc, xc, yc, xc + x, yc - y, c);
        DrawCartesianLine(hdc, xc, yc, xc + y, yc - x, c);
    }
    if (q == "2") {
        DrawCartesianLine(hdc, xc, yc, xc - x, yc - y, c);
        DrawCartesianLine(hdc, xc, yc, xc - y, yc - x, c);
    }
    if (q == "3") {
        DrawCartesianLine(hdc, xc, yc, xc - x, yc + y, c);
        DrawCartesianLine(hdc, xc, yc, xc - y, yc + x, c);
    }
    if (q == "4") {
        DrawCartesianLine(hdc, xc, yc, xc + x, yc + y, c);
        DrawCartesianLine(hdc, xc, yc, xc + y, yc + x, c);
    }

}

void fillCircleWithLines(HDC hdc, int xc, int yc,string q, int r, COLORREF c) {
    int x = 0;
    int y = r;
    int rad = r;
    int d = 1 - rad;
    int d1 = 3;
    int d2 = 5 - 2 * rad;
    //int quarter = 1;
    DrawCircleModifiedMidpoint(hdc, xc, yc, r, c);
    //-->
    //cout << "enter quarter"<<endl;
    //cin >> quarter;
    generateLines(hdc, xc, yc, x, y, c, q);
    //
    while (x < y) {
        if (d <= 0) {
            d += d1;
            d2 += 2;
        } else {
            d += d2;
            d2 += 4;
            y--;
        }
        d1 += 2;
        x++;
        //-->
        generateLines(hdc, xc, yc, x, y, c, q);
        //
    }
    //return quarter;

}
void Draw2point(HDC hdc, int xc, int yc, int x, int y, string q, COLORREF c) {

    if (q == "4") {
        SetPixel(hdc, xc + x, yc + y, c);
        SetPixel(hdc, xc + y, yc + x, c);
    }

    if (q == "2") {
        SetPixel(hdc, xc - x, yc - y, c);
        SetPixel(hdc, xc - y, yc - x, c);
    }

    if (q == "3") {
        SetPixel(hdc, xc - y, yc + x, c);
        SetPixel(hdc, xc - x, yc + y, c);
    }

    if (q == "1") {
        SetPixel(hdc, xc + x, yc - y, c);
        SetPixel(hdc, xc + y, yc - x, c);
    }

}
void fillCircleWithCircles(HDC hdc, int xc, int yc, string q, int r, COLORREF c) {
    int x = r;
    int y = 0;

    int R2 = r * r;
    Draw8Points(hdc, xc, yc, x, y, c);
    Draw2point(hdc, xc, yc, x, y, q, c);
    while (x > y)
    {
        y++;
        x = Round(sqrt((double)(R2 - y * y)));
        Draw8Points(hdc, xc, yc, x, y,c);
        Draw2point(hdc, xc, yc, x, y, q, c);
    }

    while (r--) {
        int x = r;
        int y = 0;

        int R2 = r * r;
       // Draw8Points(hdc, xc, yc, x, y, c);
        Draw2point(hdc, xc, yc, x, y, q, c);
        while (x > y)
        {
            y++;
            x = Round(sqrt((double)(R2 - y * y)));
           //Draw8Points(hdc, xc, yc, x, y, c);
            Draw2point(hdc, xc, yc, x, y, q, c);
        }
    }



}
//////////////////////////////////////////////////////////////
void floodFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc) {
    COLORREF c;
    queue <Point> s;
    s.push(Point(x, y));
    while (!s.empty()) {
        Point p = s.front();
        s.pop();
        c = GetPixel(hdc, p.x, p.y);
        if (c == bc || c == fc) continue;
        SetPixel(hdc, p.x, p.y, fc);
        s.push(Point((p.x) + 1, p.y));
        s.push(Point((p.x) - 1, p.y));
        s.push(Point(p.x, (p.y) + 1));
        s.push(Point(p.x, (p.y) - 1));
    }
    cout << "done";
}

void recFloodFill(HDC hdc, int x, int y, COLORREF bc, COLORREF fc) {

    COLORREF c;
    c = GetPixel(hdc, x, y);
    if (c == bc || c == fc) return;
    SetPixel(hdc, x, y, fc);

    recFloodFill(hdc, x + 1, y, bc, fc);
    recFloodFill(hdc, x - 1, y, bc, fc);
    recFloodFill(hdc, x, y + 1, bc, fc);
    return recFloodFill(hdc, x, y - 1, bc, fc);
}


void fillRectWithBezier(HDC hdc, int xl, int xr, int yt, int yb, COLORREF fc) {

    Rectangle(hdc, xl, yt, xr, yb);
    int x = xr - xl;
    int xMid = x / 2;
    xMid += xl;

    int x2 = rand() % (xMid - xl + 1) + xl;
    int x3 = rand() % (xr - xMid + 1) + xMid;

    int c = yt;
    while (c <= yb) {
        //curve : (X_left - >  X_right)
        //The same Y (straight line)
        Point p1(xl, c);
        Point p2(x2, c);//
        Point p3(x3, c);//
        Point p4(xr, c);
        DrawBezierCurve(hdc, p1, p2, p3, p4,fc);
        c++;
    }
}

void fillSquareWithHermite(HDC hdc, int xs, int xe, int ys, int ye, COLORREF fc) {

    int xS = xe - xs;
    int yS = ye - ys;
    while (xS != yS) {
        if (xS > yS) {
            ye++;
        } else {
            xe++;
        }
        xS = xe - xs;
        yS = ye - ys;
    }
    Rectangle(hdc, xs, ys, xe, ye);
    int c = xs;
    while (c <= xe) {
        Point p1(c, ys);
        Point p2(c, ye);
        //slope = 0
        Point T1(0, 0);
        Point T2(0, 0);
        DrawHermiteCurve(hdc, p1, T1, p2, T2, fc);
        c++;
    }
}

//=====================================================================

#define MAXENTRIES 600
struct Entry
{
int xmin,xmax;
};
void InitEntries(Entry table[])
{
    for(int i=0;i<MAXENTRIES;i++)
    {
        table[i].xmin=INT_MAX;
        table[i].xmax=-INT_MAX;
    }
}
void ScanEdge(Point v1,Point v2,Entry table[])
{
    if(v1.y==v2.y)return;
    if(v1.y>v2.y)swap(v1,v2);
    double minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    double x=v1.x;
    int y=v1.y;
    while(y<v2.y)
        {
            if(x<table[y].xmin)table[y].xmin=(int)ceil(x);
            if(x>table[y].xmax)table[y].xmax=(int)floor(x);
                y++;
                x+=minv;
        }
}
void DrawSanLines(HDC hdc,Entry table[],COLORREF color)
{
    for(int y=0;y<MAXENTRIES;y++)
    if(table[y].xmin<table[y].xmax)
    for(int x=table[y].xmin;x<=table[y].xmax;x++)
            SetPixel(hdc,x,y,color);
}

void ConvexFill(HDC hdc,Point p[],int n,COLORREF color)
{
    Entry *table=new Entry[MAXENTRIES];
    InitEntries(table);
    Point v1=p[n-1];
    for(int i=0;i<n;i++)
    {
        Point v2=p[i];
        ScanEdge(v1,v2,table);
        v1=p[i];
    }
    DrawSanLines(hdc,table,color);
    delete table;
}
//------------------------------------------------------------------------------------------
//************************************NON Convex PoLygon************************************
struct EdgeRec {
    double x;
    double minv;
    int ymax;

    bool operator<(EdgeRec r) {
        return x < r.x;
    }
};

typedef list <EdgeRec> EdgeList;

EdgeRec InitEdgeRec(Point &v1, Point &v2) {
    if (v1.y > v2.y)swap(v1, v2);
    EdgeRec rec;
    rec.x = v1.x;
    rec.ymax = v2.y;
    rec.minv = (double) (v2.x - v1.x) / (v2.y - v1.y);
    return rec;
}

void InitEdgeTable(Point *polygon, int n, EdgeList table[]) {
    Point v1 = polygon[n - 1];
    for (int i = 0; i < n; i++) {
        Point v2 = polygon[i];
        if (v1.y == v2.y) {
            v1 = v2;
            continue;
        }
        EdgeRec rec = InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1 = polygon[i];
    }
}

void GeneralPolygonFill(HDC hdc, Point *polygon, int n, COLORREF c) {
    EdgeList *table = new EdgeList[MAXENTRIES];
    InitEdgeTable(polygon, n, table);
    int y = 0;
    while (y < MAXENTRIES && table[y].size() == 0) { y++; }
    if (y == MAXENTRIES) { return; }
    EdgeList ActiveList = table[y];
    while (ActiveList.size() > 0) {
        ActiveList.sort();
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++) {
            int x1 = (int) ceil(it->x);
            it++;
            int x2 = (int) floor(it->x);
            for (int x = x1; x <= x2; x++)SetPixel(hdc, x, y, c);
        }
        y++;
        EdgeList::iterator it = ActiveList.begin();
        while (it != ActiveList.end())
            if (y == it->ymax) it = ActiveList.erase(it); else it++;
        for (EdgeList::iterator it = ActiveList.begin(); it != ActiveList.end(); it++)
            it->x += it->minv;
        ActiveList.insert(ActiveList.end(), table[y].begin(), table[y].end());
    }
    delete[] table;
}

#endif // FILLING_H_INCLUDED
