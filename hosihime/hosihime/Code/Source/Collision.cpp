#include "Collision.h"

#define PI 3.141592
#define RTOD(RAD) ((RAD)*(180/PI))
#define DTOR(DEG) ((DEG)*(PI/180))
#include <cmath>
Collision::Collision()
{
}

const bool Collision::rect_Circle(const MyRectangle* rect, const Circle* circle)const
{
	GSvector2 vertex[4]=
	{
		rect->getPosition(),//0
		rect->getPosition() + GSvector2(rect->getWidth(), 0),//1
		rect->getPosition() + GSvector2(0, rect->getHeight()),//2
		rect->getPosition() + rect->getSize()//3
	};
	for (int i = 0; i <4; i++)
	{
		//‹éŒ`‚ÌŠe“_‚Æ‰~“¯Žm‚Ì“–‚½‚è”»’è
		if (circle->isCollision(&Circle(vertex[i], 0)))
		{
			return true;
		}
	}
	int n[4]=
	{
		2,-1,1,-2
	};
	for (int i = 0; i <4; i++)
	{
		if (cricle_Segment(circle, &Segment(vertex[i], vertex[i + n[i]])))
		{
			return true;
		}
	}
	return isRectInCircle(rect,circle);
}
const bool Collision::cricle_Segment(const Circle* circle, const Segment* segment)const
{
	GSvector2 v = segment->vector();
	float r2 = circle->radius * circle->radius;
	GSvector2 v1 = circle->center - segment->p1;
	float t = gsVector2Dot(&v, &v1) / gsVector2Dot(&v, &v);

	if (t < 0 && v1.lengthSq() <= r2)
	{
		return true;
	}

	GSvector2 v2 = circle->center - segment->p2;
	if ((1 < t) && (v2.lengthSq() <= r2))
	{
		return true;
	}

	GSvector2 vt = t * v;
	GSvector2 vn = v1 - vt;
	if ((0 <= t) && (t <= 1) && vn.lengthSq() <= r2)
	{
		return true;
	}
	return false;
}
const bool Collision::isRectInCircle(const MyRectangle* rect, const Circle* circle)const
{

	Segment seg1(rect->getPosition(), rect->getPosition() + GSvector2(rect->getWidth(), 0));//0,1
	Segment seg2(rect->getPosition() + rect->getSize(),rect->getPosition() + GSvector2(0, rect->getHeight()));//3,2
	float res1 = segment_Point_atan(&seg1,&circle->center);
	float res2 = segment_Point_atan(&seg2,&circle->center);
	if (0 <= res1 && res1 <= 90 &&
		0 <= res2&& res2 <= 90)
	{
		return true;
	}
	return false;
}

const float Collision::segment_Point_atan(const Segment* segment, const GSvector2* point)const
{
	GSvector2 pp = segment->vector();
	GSvector2 pm = *point - segment->p2;

	float dot = gsVector2Dot(&pp,&pm);
	float ccw = gsVector2CCW(&pp, &pm);

	return RTOD(std::atan2(ccw, dot));
}