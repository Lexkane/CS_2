#pragma once
#include "main.h"

class Point
{
protected:
	double x, y;

public:
	Point(int=0, int=0);

	bool operator==(const Point&) const;

	double distance(const Point&) const;
	double isCorrect(const Point&, const Point&) const;

	void print();

	friend istream& operator>>(istream&, Point&);
};

Point::Point(int _x, int _y): x(_x), y(_y)
{}

double Point::distance(const Point& p) const
{
	return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
}

double Point::isCorrect(const Point& p1, const Point& p2) const
{
	if ( *this == p1 || p1 == p2 || *this == p2 )
		return false;

	if ( x == p1.x && x == p2.x )
		return false;

	if ( y == p1.y && y == p2.y )
		return false;
	
	return true;

	//if ( distance(p1) == p1.distance(p2) && p1.distance(p2) == distance(p2) )
//		return true;
//	else
		//return false;
}

bool Point::operator==(const Point& p) const
{
	if ( x == p.x && y == p.y )
		return true;

	return false;
}

void Point::print()
{
	cout << "X: " << x << ", Y: " << y << endl;
}

istream& operator>>(istream& is, Point& p)
{
	is >> p.x >> p.y;
	return is;
}