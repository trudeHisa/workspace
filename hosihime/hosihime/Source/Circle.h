#ifndef _CIRCLE_H_
#define _CIRCLE_H_
#include <GSvector2.h>
class Circle
{
public:
	Circle(const GSvector2& center,float radius);
	~Circle();
	const bool isCollision(const Circle& other)const;
	void expand(float _radius);
	void translate(const GSvector2& position);
private:
	GSvector2 center;
	float radius;
};
#endif