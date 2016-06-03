#include "Circle.h"

Circle::Circle(const GSvector2& center, float radius)
	:center(center), radius(radius)
{
}

Circle::~Circle()
{
}
const bool Circle::isCollision(const Circle& other)const
{
	float dis = gsVector2Distance(&center,&other.center);
	return dis <= radius + other.radius;
}
void Circle::expand(float _radius)
{
	radius = _radius;
}
void Circle::translate(const GSvector2& position)
{
	center += position;
}