#ifndef _INPUT_H_
#define _INPUT_H_
#include <gslib.h>
class Input
{
public:
	Input();
	const bool getActionTrigger()const;
	const GSvector2& getVelocity()const;
	const float getHorizontal()const;//êÖïΩ	
	const float getVertical()const;//êÇíº
	const bool getUpTrigger()const;
	const bool getDownTrigger()const;
public:
	const bool getDebugResetTrigger()const;
};
#endif