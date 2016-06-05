
#include "Segment.h"


Segment::Segment(const GSvector2& p1, const GSvector2& p2)
	:p1(p1), p2(p2)
{
}

const GSvector2& Segment::vector()const
{
	return p2 - p1;
}
const bool Segment::isCollision(const Segment* other)const
{
	GSvector2 v = other->p1 - this->p1;
	float ccw_v1_v2 = gsVector2CCW(&this->vector(), &other->vector());
	if (ccw_v1_v2 == 0.0f)
	{
		// •½só‘Ô
		return false;
	}

	float ccw_v_v2 = gsVector2CCW(&v, &this->vector());
	float ccw_v_v1 = gsVector2CCW(&v, &other->vector());

	float t1 = ccw_v_v1 / ccw_v_v2;
	float t2 = ccw_v_v2 / ccw_v_v1;

	if (t1 < 0 || t1 > 1 || t2 < 0 || t2  > 1)
	{
		// Œğ·‚µ‚Ä‚¢‚È‚¢
		return false;
	}
	return true;
}