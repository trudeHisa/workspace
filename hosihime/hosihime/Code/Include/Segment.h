/**
*@file Segment.h
*@brief ü•ª
*@author matuo
*@data 2016/6/05
*/
#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include <GSvector2.h>
class Segment
{
public:
	Segment(const GSvector2& p1,const GSvector2& p2);
    const GSvector2& vector()const;
	const bool isCollision(const Segment* other)const;
	GSvector2 p1;
	GSvector2 p2;
};
#endif
