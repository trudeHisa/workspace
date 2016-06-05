/**
*@file Collision.h
*@brief �����蔻��
*@author matuo
*@data 2016/6/05
*/
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "Circle.h"
#include"MyRectangle.h"
#include "Segment.h"

class Collision
{
public:
	Collision();
private:
	/**
	*@fn ��`�Ɖ~�̓����蔻��
	*/
	const bool rect_Circle(const MyRectangle* rect, const Circle* circle)const;
	/**
	*@fn �����Ɖ~�̓����蔻��
	*/
	const bool cricle_Segment(const Circle* circle, const Segment* segment)const;

	const bool isRectInCircle(const MyRectangle* rect, const Circle* circle)const;
	const float segment_Point_atan(const Segment* segment, const GSvector2* point)const;
};

#endif

