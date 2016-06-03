#include "Input.h"

Input::Input()
{
}
const bool Input::getActionTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_SPACE);
}
const GSvector2& Input::getVelocity()const
{
	GSvector2 vel(getHorizontal(),getVertical());
	return vel.normalize();
}
//êÖïΩ	
const float Input::getHorizontal()const
{
	float f = gsGetKeyState(GKEY_RIGHT);
	f -= gsGetKeyState(GKEY_LEFT);
	return f;
}
//êÇíº
const float Input::getVertical()const
{
	float f = gsGetKeyState(GKEY_UP);
	f -= gsGetKeyState(GKEY_DOWN);
	return f;
}
const bool Input::getDebugResetTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_R);
}
const bool Input::getUpTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_UP);
}
const bool Input::getDownTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_DOWN);
}