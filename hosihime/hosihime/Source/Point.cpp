#include "Point.h"

Point::Point()
{
	x = y = 0;
}
Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

Point::Point(const Point& _p)
{
	x = _p.x;
	y = _p.y;
}

Point&  Point::operator +(){ return *this; }
Point&  Point::operator -(){ return Point(-x, -y); }
Point& Point::operator +=(const Point& p)
{
	x += p.x;
	y += p.y;
	return *this;
}
Point& Point::operator -=(const Point& p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}
Point& Point::operator *=(int i)
{
	x *= i;
	y *= i;
	return *this;
}
Point& Point::operator /=(const Point& p)
{
	x /= p.x;
	y /= p.y;
	return *this;
}
Point& Point::operator /=(int i)
{
	x /= i;
	y /= i;
	return *this;
}
bool Point::operator ==(const Point& p)
{
	return x == p.x&&y == p.y;
}
bool Point::operator !=(const Point& p)
{
	return !(*this == p);
}
bool Point::operator >=(const Point& p)
{
	return (x >= p.x&&y >= p.y);
}
bool Point::operator >(const Point& p)
{
	return (x > p.x&&y > p.y);
}
bool Point::operator <=(const Point& p)
{
	return !(*this > p);
}
bool Point::operator <(const Point& p)
{
	return !(*this >= p);
}
//‚Q€‰‰Zq
const Point operator +(const Point& p1, const Point& p2)
{
	Point temp(p1);
	return temp += p2;
}
const Point operator -(const Point& p1, const Point& p2)
{
	Point temp(p1);
	return temp -= p2;
}
const Point operator *(const Point& p, int i)
{
	Point temp(p);
	return temp *= i;
}
const Point operator /(const Point& p, int i)
{
	Point temp(p);
	return temp /= i;
}
const Point operator /(int i, const Point& p)
{
	return Point(i / p.x, i/ p.y);
}