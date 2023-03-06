#include <Windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <CommCtrl.h>
#include <tchar.h>
#include <math.h>
#include "Ellipse.h"
#include "Line.h"
#include "Circle.h"
#include "Curves.h"
#include "Filling.h"
#include "Clipping.h"
using namespace std;

class Drawing
{
public:
	string name;
	vector<Point> points;
    COLORREF bColor, color;
};

/*=========================================================================================================*/

vector <Drawing> drawings;
bool save = false, load = false, clear = false, exitt = false;
bool lineDDA = false, lineParametric = false, lineMidPoint = false;
bool cDirect = false, cPolar = false, cIterativePolar = false, cMidPoint1 = false, cModifiedMidPoint = false;
bool ellipseDirect = false, ellipsePolar = false, ellipsePolarIterative = false, ellipseMidPoint = false;
bool hermiteCurve = false, bezierCurve = false, cardinalSpline = false;
bool fillCLines = false, fillsHermite = false, fillRectBezier = false, fillPo = false, fillGeneral = false, recFlood = false, floodfill = false;
bool pointRecClip = false, lineRecClip = false, polygonRecClip = false, pointSqClip = false, lineSqClip = false, pointCClip = false, LineCClip = false, rect = false, square = false, circle = false;
bool cl = false, fillCC = false, q1 = false, q2 = false , q3 = false, q4 = false;
COLORREF color, bColor;
static int cnt = 0, length;
Point p1, p2, p3, p4, p5,p6, t1, t2;
string q;
vector<Point>points;
vector <Point> rec;

void setAll()
{
	save = false, load = false, clear = false, exitt = false;
	lineDDA = false, lineParametric = false, lineMidPoint = false;
	cDirect = false, cPolar = false, cIterativePolar = false, cMidPoint1 = false, cModifiedMidPoint = false;
	ellipseDirect = false, ellipsePolar = false, ellipsePolarIterative = false, ellipseMidPoint = false;
	hermiteCurve = false, bezierCurve = false, cardinalSpline = false;
	fillCLines = false, fillsHermite = false, fillRectBezier = false, fillPo = false, fillGeneral = false, recFlood = false, floodfill = false;
	pointRecClip = false, lineRecClip = false, polygonRecClip = false, pointSqClip = false, lineSqClip = false, pointCClip = false, LineCClip = false, rect = false, square = false, circle = false;
	cl = false , fillCC = false, q1 = false, q2 = false , q3 = false, q4 = false;
	points.clear();
}

/*=========================================================================================================*/

void add(string name, vector<Point> points, COLORREF bColor, COLORREF color) { //-->
	Drawing a;
	a.name = name;
	a.points = points;
    a.bColor= bColor;
    a.color= color;
	drawings.push_back(a);
}

/*=========================================================================================================*/

void draw(Drawing a, HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	cout << "Action : " << a.name << endl;

	if (a.name == "DrawLineDDA") {
		DrawLineDDA(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y, a.color);
	}
	else if (a.name == "DrawLineMidPoint") {
		drawLineMidPoint(hdc, a.points[0], a.points[1], a.color);
	}
	else if (a.name == "DrawLineParametric") {
		DrawLineParametric(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y, a.color);
	}
	/*----------------------------------*/
	else if (a.name == "DrawCircleDirect") {
		DrawCircleDirect(hdc, a.points[0], a.points[1], a.color);
	}
	else if (a.name == "DrawCirclePolar") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		DrawCirclePolar(hdc, a.points[0].x, a.points[0].y, r, a.color);
	}
	else if (a.name == "DrawCircleIterativePolar") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		DrawCircleIterativePolar(hdc, a.points[0].x, a.points[0].y, r, a.color);
	}
	else if (a.name == "DrawCircleMidPoint") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		DrawCircleMidpoint(hdc, a.points[0].x, a.points[0].y, r, a.color);
	}
	else if (a.name == "DrawCircleModifiedMidPoint") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		DrawCircleModifiedMidpoint(hdc, a.points[0].x, a.points[0].y, r, a.color);
	}
	/*----------------------------------*/
	else if (a.name == "DrawEllipseDirect") {
		DrawEllipseDirect(hdc, a.points[0], a.points[1], a.points[2], a.color);
	}
	else if (a.name == "DrawEllipsePolar") {
		DrawEllipsePolar(hdc, a.points[0], a.points[1], a.points[2], a.color);
	}
	else if (a.name == "DrawEllipsePolarIterative") {
		DrawEllipsePolarIterative(hdc, a.points[0], a.points[1], a.points[2], a.color);
	}
	else if (a.name == "DrawEllipseMidPoint") {
		DrawEllipseMidPoint(hdc, a.points[0], a.points[1], a.points[2], a.color);
	}
	/*----------------------------------*/
	else if (a.name == "DrawHermiteCurve") {
		DrawHermiteCurve(hdc, a.points[0], a.points[1], a.points[2], a.points[3], a.color);
	}
	else if (a.name == "DrawBezierCurve") {
		DrawBezierCurve(hdc, a.points[0], a.points[1], a.points[2], a.points[3], a.color);
	}
	else if (a.name == "DrawCardinalSpline") {
		DrawCardinalSpline(hdc, a.points, 6, 0, a.color);
	}
	/*----------------------------------*/
	else if (a.name.substr(0,a.name.size()-1) == "FillCircleLines") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		q = a.name[a.name.size()-1];
		fillCircleWithLines(hdc, a.points[0].x, a.points[0].y,q, r, a.color);
	}
	else if (a.name.substr(0,a.name.size()-1) == "FillCircleCircles") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		q = a.name[a.name.size()-1];
		fillCircleWithCircles(hdc, a.points[0].x, a.points[0].y,q, r, a.color);
	}
	else if (a.name == "FillSquareHermite") {
		int r = sqrt((a.points[0].x - a.points[1].x) * (a.points[0].x - a.points[1].x) + (a.points[0].y - a.points[1].y) * (a.points[0].y - a.points[1].y));
		fillSquareWithHermite(hdc, a.points[0].x, a.points[1].x, a.points[0].y, a.points[1].y, a.color);
	}
	else if (a.name == "FillRectBezier") {
		fillRectWithBezier(hdc, a.points[0].x, a.points[1].x, a.points[0].y, a.points[1].y, a.color);
	}
	else if (a.name == "ConvexPolygon") {
		Point p[5];
		for(int i =0 ; i< a.points.size(); i++){
            p[i] = a.points[i];
		}
		ConvexFill(hdc, p, 5, a.color);
	}
	else if (a.name == "Non-ConvexPloygon") {
		Point* tmp = new Point[a.points.size()];

		for(int i =0 ; i< a.points.size(); i++){
            tmp[i] = a.points[i];
		}
		GeneralPolygonFill(hdc, tmp, 5, a.color);
	}
	else if (a.name == "Recursive-FloodFill") {
		recFloodFill(hdc, a.points[0].x, a.points[0].y, a.bColor, a.color);
	}
    else if (a.name == "NonRecursive-FloodFill") {
		floodFill(hdc, a.points[0].x, a.points[0].y, a.bColor, a.color);
	}
	/*----------------------------------*/
	// ----> Rectangle
    else if (a.name == "Rectangle") {
        t1.x = a.points[0].x;
        t1.y = a.points[0].y;
        t2.x = a.points[1].x;
        t2.y = a.points[1].y;
		Rectangle(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y);
	}
	else if (a.name == "PointClipping-Rectangle") {
		RecPointClipping(hdc, a.points[0].x, a.points[0].y, t1.x, t1.y, t2.x, t2.y, a.color);
	}
	else if (a.name == "LineClipping-Rectangle") {

		RecCohenSuth(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y, t1.x, t1.y, t2.x, t2.y, a.color);
	}
	else if (a.name == "PolygonClipping-Rectangle") {

		vector<Point> p;
		for(int i = 0 ; i < a.points.size() ; i++){
           p.push_back(a.points[i]);
		}
		RecPolygonClip(hdc, p, t1.x, t1.y, t2.x, t2.y, a.color);
	}
    else if (a.name == "Square") {

        t1.x = a.points[0].x;
        t1.y = a.points[0].y;
        t2.x = a.points[1].x;
        t2.y = a.points[1].y;
        length = getLength(a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y);
		DrawSquare(hdc, a.points[0].x, a.points[0].y, length);
	}
	else if (a.name == "PointClipping-Square") {
		SquarePointClipping(hdc, a.points[0].x, a.points[0].y, t1.x, t1.y, length, a.color);
	}
	else if (a.name == "LineClipping-Square") {
		SquareCohenSuth(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y, t1.x, t1.y, length, a.color);
	}
	//Circle
	else if (a.name == "Circle") {
        t1.x = a.points[0].x;
		t1.y = a.points[0].y;
		length = getLength(a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y);
		DrawCircleDirect(hdc, a.points[0], a.points[1], a.color);
	}
	else if (a.name == "PointClipping-Circle") {
		CirclePointClipping(hdc, a.points[0].x, a.points[0].y, t1.x, t1.y, length, a.color);

	}
	else if (a.name == "LineClipping-Circle") {
		CircleLineClipping(hdc, a.points[0].x, a.points[0].y, a.points[1].x, a.points[1].y, t1.x, t1.y, length, a.color);
	}

	ReleaseDC(hwnd, hdc);
}

/*=========================================================================================================*/

void SaveData()		//save function for all data in screen in file
{
	ofstream f;
	f.open("file.txt");
	int size = drawings.size();
	cout << "size = " << size << endl;
	for (int i = 0; i < size; i++) {
		cout << "Action Name : " << drawings[i].name << endl;
		f << drawings[i].name;
		f << " ";
		f << drawings[i].points.size();
		f << " ";
		for (int j = 0; j < drawings[i].points.size(); j++) {
			cout << "Point " << j + 1 << ": (" << drawings[i].points[j].x << "," << drawings[i].points[j].y << ") " << endl;
			f << drawings[i].points[j].x << " " << drawings[i].points[j].y << " ";
		}
        f << drawings[i].bColor;
        f << " ";
        f << drawings[i].color;
        f << " ";

	}

	f.close();

}

/*=========================================================================================================*/

void LoadData(HWND hwnd)		//load function to load data from file
{
	int size;
	ifstream f("file.txt");
	vector<Drawing> ac;
	if (!f.is_open())
	{
		cout << "File doesn't exist !!" << endl;
	}
	else {
		while (!f.eof())
		{
			Drawing a;
			int len;
			f >> a.name;
			cout << a.name << endl;
			if (f.eof()) break;
			f >> len;

			for (int i = 0; i < len; i++) {
				Point p;
				f >> p.x;
				f >> p.y;
				a.points.push_back(p);
			}
            f >> a.bColor;
            f >> a.color;
			ac.push_back(a);

		}

		f.close();
		for (int i = 0; i < ac.size(); i++) {
			draw(ac[i], hwnd);
		}
	}
}

/*=========================================================================================================*/

LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	static HWND lineHWND;
	static HWND circleHWND;
	static HWND ellipseHWND;
	static HWND curveHWND;
	static HWND colorHWND;
	static HWND fillingHWND;
	static HWND clipHWND;
	static HWND info;
	static HWND numHWND;
	static int x[100];
	static int y[100];
	static Drawing action;
	static COLORREF color;

	switch (mcode)
	{
	case WM_CREATE:
		info = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			0, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(info, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Save"));
		SendMessage(info, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Load"));
		SendMessage(info, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Clear"));
		SendMessage(info, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Exit"));

		lineHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			150, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(lineHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineDDA"));
		SendMessage(lineHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineMidPoint"));
		SendMessage(lineHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineParametric"));

		circleHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			300, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(circleHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("CircleDirect"));
		SendMessage(circleHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("CirclePolar"));
		SendMessage(circleHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("CircleIterativePolar"));
		SendMessage(circleHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("CircleMidPoint"));
		SendMessage(circleHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("CircleModifiedMidPoint"));

		ellipseHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			450, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(ellipseHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("EllipseDirect"));
		SendMessage(ellipseHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("EllipsePolar"));
		SendMessage(ellipseHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("EllipsePolarIterative"));
		SendMessage(ellipseHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("EllipseMidPoint"));

		curveHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			600, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(curveHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("HermiteCurve"));
		SendMessage(curveHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("BezierCurve"));
		SendMessage(curveHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("DrawCardinalSpline"));

		colorHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			750, 0, 150, 550, hwnd, NULL, NULL, NULL);
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Red"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Green"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Blue"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Yellow"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Black"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Orange"));
		SendMessage(colorHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Purple"));

		fillingHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			900, 0, 200, 550, hwnd, NULL, NULL, NULL);
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("FillCircleLines"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("FillCircleCircles"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("FillSquareHermite"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("FillRectBezier"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("ConvexPolygon"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Non-ConvexPolygon"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Recursive-FloodFill"));
		SendMessage(fillingHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("NonRecursive-FloodFill"));

		clipHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			1100, 0, 200, 550, hwnd, NULL, NULL, NULL);
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Rectangle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("PointClipping-Rectangle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineClipping-Rectangle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("PolygonClipping-Rectangle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Square"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("PointClipping-Square"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineClipping-Square"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("Circle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("PointClipping-Circle"));
		SendMessage(clipHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("LineClipping-Circle"));

		numHWND = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			1300, 0, 100, 550, hwnd, NULL, NULL, NULL);
		SendMessage(numHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("1"));
		SendMessage(numHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("2"));
		SendMessage(numHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("3"));
		SendMessage(numHWND, (UINT)CB_ADDSTRING, 0, (LPARAM)TEXT("4"));

		break;

	case WM_COMMAND:
		if (HIWORD(wp) == CBN_SELCHANGE)
		{
			int ItemIdx = SendMessage((HWND)lp, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			TCHAR ListItem[256];
			(TCHAR)SendMessage((HWND)lp, (UINT)CB_GETLBTEXT, (WPARAM)ItemIdx, (LPARAM)ListItem);
			if (!_tcscmp(ListItem, _T("Red"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(255, 0, 0);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Green"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(124, 252, 0);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Blue"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(0, 0, 255);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Yellow"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(255, 255, 0);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Black"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(0, 0, 0);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Orange"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(255, 140, 0);
				cl = true;
			}
			else if (!_tcscmp(ListItem, _T("Purple"))) {
				SendMessage(colorHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				color = RGB(128, 0, 128);
				cl = true;
			}

			/*-----------------------------------------------------*/
			if (!_tcscmp(ListItem, _T("LineDDA"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "LineDDA";
				setAll();
				lineDDA = true;
			}
			else if (!_tcscmp(ListItem, _T("LineMidPoint"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "LineMidPoint";
				setAll();
				lineMidPoint = true;
			}
			else if (!_tcscmp(ListItem, _T("LineParametric"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "LineParametric";
				setAll();
				lineParametric = true;
			}
			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("Save"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				save = true;
			}
			else if (!_tcscmp(ListItem, _T("Load"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				load = true;
			}
			else if (!_tcscmp(ListItem, _T("Clear"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				clear = true;
			}
			else if (!_tcscmp(ListItem, _T("Exit"))) {
				SendMessage(lineHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				exitt = true;
			}
			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("CircleDirect"))) {
				SendMessage(circleHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "CircleDirect";
				setAll();
				cDirect = true;
			}
			else if (!_tcscmp(ListItem, _T("CirclePolar"))) {
				SendMessage(circleHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "CirclePolar";
				setAll();
				cPolar = true;
			}
			else if (!_tcscmp(ListItem, _T("CircleIterativePolar"))) {
				SendMessage(circleHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "CircleIterativePolar";
				setAll();
				cIterativePolar = true;
			}
			else if (!_tcscmp(ListItem, _T("CircleMidPoint"))) {
				SendMessage(circleHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "CircleMidPoint";
				setAll();
				cMidPoint1 = true;
			}
			else if (!_tcscmp(ListItem, _T("CircleModifiedMidPoint"))) {
				SendMessage(circleHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "CircleModifiedMidPoint";
				setAll();
				cModifiedMidPoint = true;
			}
			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("EllipseDirect"))) {
				SendMessage(ellipseHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				ellipseDirect = true;

			}
			else if (!_tcscmp(ListItem, _T("EllipsePolar"))) {
				SendMessage(ellipseHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				ellipsePolar = true;
			}
			else if (!_tcscmp(ListItem, _T("EllipsePolarIterative"))) {
				SendMessage(ellipseHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				ellipsePolarIterative = true;
			}
			else if (!_tcscmp(ListItem, _T("EllipseMidPoint"))) {
				SendMessage(ellipseHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				ellipseMidPoint = true;
			}
			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("HermiteCurve"))) {
				SendMessage(curveHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				hermiteCurve = true;
			}
			else if (!_tcscmp(ListItem, _T("BezierCurve"))) {
				SendMessage(curveHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				bezierCurve = true;
			}
			else if (!_tcscmp(ListItem, _T("DrawCardinalSpline"))) {
				SendMessage(curveHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				cardinalSpline = true;
			}

			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("FillCircleLines"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "FillCircleLines";
				setAll();
				fillCLines = true;
			}
			else if (!_tcscmp(ListItem, _T("FillCircleCircles"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "FillCircleCircles";
				setAll();
				fillCC = true;
			}
			else if (!_tcscmp(ListItem, _T("FillSquareHermite"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "FillSquareHermite";
				setAll();
				fillsHermite = true;
			}
			else if (!_tcscmp(ListItem, _T("FillRectBezier"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "FillRectBezier";
				setAll();
				fillRectBezier = true;
			}
			else if (!_tcscmp(ListItem, _T("ConvexPolygon"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "ConvexPolygon";
				setAll();
				fillPo = true;
			}
			else if (!_tcscmp(ListItem, _T("Non-ConvexPolygon"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "Non-ConvexPolygon";
				setAll();
				fillGeneral = true;
			}
			else if (!_tcscmp(ListItem, _T("Recursive-FloodFill"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "Recursive-FloodFill";
				setAll();
				recFlood = true;
			}
			else if (!_tcscmp(ListItem, _T("NonRecursive-FloodFill"))) {
				SendMessage(fillingHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				action.name = "NonRecursive-FloodFill";
				setAll();
				floodfill = true;
			}
			/*-----------------------------------------------------*/
			else if (!_tcscmp(ListItem, _T("Rectangle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "Rectangle";
				rect = true;
			}
			else if (!_tcscmp(ListItem, _T("Square"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "Square";
				square = true;
			}
			else if (!_tcscmp(ListItem, _T("Circle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "Circle";
				circle = true;
			}

			else if (!_tcscmp(ListItem, _T("PointClipping-Rectangle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "PointClipping-Rectangle";
				pointRecClip = true;
			}
			else if (!_tcscmp(ListItem, _T("LineClipping-Rectangle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "LineClipping-Rectangle";
				lineRecClip = true;
			}
			else if (!_tcscmp(ListItem, _T("PolygonClipping-Rectangle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "PolygonClipping-Rectangle";
				polygonRecClip = true;
			}
			else if (!_tcscmp(ListItem, _T("PointClipping-Square"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "PointClipping-Square";
				pointSqClip = true;
			}
			else if (!_tcscmp(ListItem, _T("LineClipping-Square"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "LineClipping-Square";
				lineSqClip = true;
			}
			else if (!_tcscmp(ListItem, _T("PointClipping-Circle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "PointClipping-Circle";
				pointCClip = true;
			}
			else if (!_tcscmp(ListItem, _T("LineClipping-Circle"))) {
				SendMessage(clipHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				action.name = "LineClipping-Circle";
				LineCClip = true;
			}
			else if (!_tcscmp(ListItem, _T("1"))) {
				SendMessage(numHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				q = "1";
				q1 = true;
			}
			else if (!_tcscmp(ListItem, _T("2"))) {
				SendMessage(numHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				q = "2";
				q2 = true;
			}
			else if (!_tcscmp(ListItem, _T("3"))) {
				SendMessage(numHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				q = "3";
				q3 = true;
			}
			else if (!_tcscmp(ListItem, _T("4"))) {
				SendMessage(numHWND, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				setAll();
				q = "4";
				q4 = true;
			}
		}

		break;
    case WM_RBUTTONDOWN:
        if (clear) {
			HDC hdc = GetDC(hwnd);
			InvalidateRect(hwnd, NULL, true);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (load) {
			LoadData(hwnd);
			cnt = 0;
		}
		else if (save) {
			SaveData();
			cnt = 0;
		}
		else if (exitt) {
			cnt = 0;
			exit(0);
		}
        break;
	case WM_LBUTTONDOWN:

		/*-----------------------------------------------------*/
		if (cnt == 0) {
			cout << "First Point" << endl;
			p1.x = LOWORD(lp);
			p1.y = HIWORD(lp);
			points.push_back(p1);
			cnt++;

		}
		else if (cnt == 1) {
			cout << "Second Point" << endl;
			p2.x = LOWORD(lp);
			p2.y = HIWORD(lp);
			points.push_back(p2);
			cnt++;

		}
		else if (cnt == 2) {
			cout << "Third Point" << endl;
			p3.x = LOWORD(lp);
			p3.y = HIWORD(lp);
			points.push_back(p3);
			cnt++;

		}
		else if (cnt == 3) {
			cout << "Fourth Point" << endl;
			p4.x = LOWORD(lp);
			p4.y = HIWORD(lp);
			points.push_back(p4);
			cnt++;

		}
		else if (cnt == 4) {
			cout << "Fifth Point" << endl;
			p5.x = LOWORD(lp);
			p5.y = HIWORD(lp);
			points.push_back(p5);
			cnt++;

		}
		else if (cnt == 5) {
			cout << "Sixth Point" << endl;
			p6.x = LOWORD(lp);
			p6.y = HIWORD(lp);
			points.push_back(p6);
			cnt++;

		}
		/*-----------------------------------------------------*/
		if (lineDDA && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			DrawLineDDA(hdc, p1.x, p1.y, p2.x, p2.y, color);
			add("DrawLineDDA", points, bColor,color);
			ReleaseDC(hwnd, hdc);
			points.clear();
			cnt = 0;

		}
		else if (lineParametric && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawLineParametric(hdc, p1.x, p1.y, p2.x, p2.y, color);
			add("DrawLineParametric", points, bColor,color);
			points.clear();
			ReleaseDC(hwnd, hdc);
		}
		else if (cnt >= 2 && lineMidPoint && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			drawLineMidPoint(hdc, p1, p2, color);
			add("DrawLineMidPoint", points, bColor,color);
			points.clear();
			ReleaseDC(hwnd, hdc);
		}
		/*-----------------------------------------------------*/
		else if (cDirect && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			DrawCircleDirect(hdc, p1, p2, color);
			add("DrawCircleDirect", points, bColor,color);
			cnt = 0;
			bColor = color;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (cPolar && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			DrawCirclePolar(hdc, p1.x, p1.y, r, color);
			add("DrawCirclePolar", points, bColor,color);
			cnt = 0;
			bColor = color;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (cIterativePolar && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			DrawCircleIterativePolar(hdc, p1.x, p1.y, r, color);
			add("DrawCircleIterativePolar", points, bColor,color);
			cnt = 0;
			bColor = color;
			points.clear();
			ReleaseDC(hwnd, hdc);
		}
		else if (cMidPoint1 && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			DrawCircleMidpoint(hdc, p1.x, p1.y, r, color);
			add("DrawCircleMidPoint", points, bColor,color);
			cnt = 0;
			bColor = color;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (cModifiedMidPoint && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			DrawCircleModifiedMidpoint(hdc, p1.x, p1.y, r, color);
			add("DrawCircleModifiedMidPoint", points, bColor,color);
			cnt = 0;
			bColor = color;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		/*-----------------------------------------------------*/
		else if (fillCLines && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			fillCircleWithLines(hdc, p1.x, p1.y,q, r, color);
			string name = "FillCircleLines" + q;
			add(name, points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (fillCC && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			int r = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));

			fillCircleWithCircles(hdc, p1.x, p1.y,q, r, color);
			string name = "FillCircleCircles" + q;
			add(name, points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (fillsHermite && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			fillSquareWithHermite(hdc, p1.x, p2.x, p1.y, p2.y, color);
			add("FillSquareHermite", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (fillRectBezier && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			fillRectWithBezier(hdc, p1.x, p2.x, p1.y, p2.y, color);
			add("FillRectBezier", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (fillPo && cnt >= 5 && cl) {
			HDC hdc = GetDC(hwnd);
			Point v[5] = { p1,p2,p3,p4,p5 };
			ConvexFill(hdc, v, 5, color);
			add("ConvexPolygon", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (fillGeneral && cnt >= 5 && cl) {
			HDC hdc = GetDC(hwnd);
			Point v[5] = { p1,p2,p3,p4,p5 };
			GeneralPolygonFill(hdc, v, 5, color);
			add("Non-ConvexPloygon", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (recFlood && cnt >= 1) {
			HDC hdc = GetDC(hwnd);
			recFloodFill(hdc, p1.x, p1.y, bColor, color);
			add("Recursive-FloodFill", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}
		else if (floodfill && cnt >= 1) {
			HDC hdc = GetDC(hwnd);
			floodFill(hdc, p1.x, p1.y, bColor, color);
			add("NonRecursive-FloodFill", points, bColor,color);
			cnt = 0;
			points.clear();
			ReleaseDC(hwnd, hdc);

		}

		/*-----------------------------------------------------*/
		else if (pointRecClip && cnt >= 1 && cl) {
			HDC hdc = GetDC(hwnd);
			RecPointClipping(hdc, p1.x, p1.y, t1.x, t1.y, t2.x, t2.y, color);
			add("PointClipping-Rectangle", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (rect && cnt >= 2) {
			HDC hdc = GetDC(hwnd);
			Rectangle(hdc, p1.x, p1.y, p2.x, p2.y);
			t1.x = p1.x;
			t1.y = p1.y;
			t2.x = p2.x;
			t2.y = p2.y;
			rec.clear();
			rec.push_back(t1);
			rec.push_back(t2);
			//Rectangle
			add("Rectangle", points, bColor,color);
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (lineRecClip && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			RecCohenSuth(hdc, p1.x, p1.y, p2.x, p2.y, t1.x, t1.y, t2.x, t2.y, color);
			add("LineClipping-Rectangle", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (polygonRecClip && cnt >= 5 && cl) {
			HDC hdc = GetDC(hwnd);
			vector<Point> v = { p1,p2,p3,p4,p5 };
			RecPolygonClip(hdc, v, t1.x, t1.y, t2.x, t2.y, color);
			add("PolygonClipping-Rectangle", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (square && cnt >= 2) {
			HDC hdc = GetDC(hwnd);
			length = getLength(p1.x, p1.y, p2.x, p2.y);
			DrawSquare(hdc, p1.x, p1.y, length);
			t1.x = p1.x;
			t1.y = p1.y;
			t2.x = p2.x;
			t2.y = p2.y;
			rec.clear();
			rec.push_back(t1);
			rec.push_back(t2);
			//Square
			add("Square", points, bColor,color);
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (pointSqClip && cnt >= 1 && cl) {
			HDC hdc = GetDC(hwnd);
			SquarePointClipping(hdc, p1.x, p1.y, t1.x, t1.y, length, color);
			add("PointClipping-Square", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (lineSqClip && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			SquareCohenSuth(hdc, p1.x, p1.y, p2.x, p2.y, t1.x, t1.y, length, color);
			add("LineClipping-Square", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (circle && cnt >= 2) {
			HDC hdc = GetDC(hwnd);
			length = getLength(p1.x, p1.y, p2.x, p2.y);
			DrawCircleDirect(hdc, p1, p2, color);
			t1.x = p1.x;
			t1.y = p1.y;
			rec.clear();
			rec.push_back(t1);
			//Circle
			add("Circle", points, bColor,color);
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (pointCClip && cnt >= 1 && cl) {
			HDC hdc = GetDC(hwnd);
			CirclePointClipping(hdc, p1.x, p1.y, t1.x, t1.y, length, color);
			add("PointClipping-Circle", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}
		else if (LineCClip && cnt >= 2 && cl) {
			HDC hdc = GetDC(hwnd);
			CircleLineClipping(hdc, p1.x, p1.y, p2.x, p2.y, t1.x, t1.y, length, color);
			add("LineClipping-Circle", points, bColor,color);
			points.clear();
			cnt = 0;
			ReleaseDC(hwnd, hdc);
		}

		/*-----------------------------------------------------*/
		else if (ellipseDirect && cnt >= 3 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawEllipseDirect(hdc, p1, p2, p3, color);
			add("DrawEllipseDirect", points, bColor,color);
			points.clear();
			bColor = color;
			ReleaseDC(hwnd, hdc);
		}
		else if (ellipsePolar && cnt >= 3 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawEllipsePolar(hdc, p1, p2, p3, color);
			add("DrawEllipsePolar", points, bColor,color);
			points.clear();
			bColor = color;
			ReleaseDC(hwnd, hdc);
		}
		else if (ellipsePolarIterative && cnt >= 3 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawEllipsePolarIterative(hdc, p1, p2, p3, color);
			add("DrawEllipsePolarIterative", points, bColor,color);
			points.clear();
			bColor = color;
			ReleaseDC(hwnd, hdc);
		}
		else if (ellipseMidPoint && cnt >= 3 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawEllipseMidPoint(hdc, p1, p2, p3, color);
			add("DrawEllipseMidPoint", points, bColor,color);
			points.clear();
			bColor = color;
			ReleaseDC(hwnd, hdc);
		}
		/*-----------------------------------------------------*/
		else if (hermiteCurve && cnt >= 4 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
            Point T1(3*(p2.x - p1.x),3*(p2.y - p1.y));
            Point T2(3*(p4.x - p3.x),3*(p4.y - p3.y));
			DrawHermiteCurve(hdc, p1, T1, p4, T2, color);
			add("DrawHermiteCurve", points, bColor,color);
			points.clear();
			ReleaseDC(hwnd, hdc);
		}
		else if (bezierCurve && cnt >= 4 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawBezierCurve(hdc, p1, p2, p3, p4, color);
			add("DrawBezierCurve", points, bColor,color);
			points.clear();
			ReleaseDC(hwnd, hdc);
		}

		else if (cardinalSpline && cnt >= 6 && cl) {
			HDC hdc = GetDC(hwnd);
			cnt = 0;
			DrawCardinalSpline(hdc, points, 6, 0, color);
			add("DrawCardinalSpline", points, bColor,color);
			points.clear();
			ReleaseDC(hwnd, hdc);
		}
		/*-----------------------------------------------------*/
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, mcode, wp, lp);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
	WNDCLASS wc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinst;
	wc.lpfnWndProc = MyWndProc;
	wc.lpszClassName = reinterpret_cast<LPCSTR>(L"MyClass");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(reinterpret_cast<LPCSTR>(L"MyClass"), reinterpret_cast<LPCSTR>(L"Project Window"), WS_OVERLAPPEDWINDOW, 0, 0, 1500, 800, NULL, NULL, hinst, 0);
	ShowWindow(hwnd, nsh);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
