#include "Input.h"

Input::Input()
{
}
const bool Input::getActionTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_SPACE)
		|| !!gsGetJoyTrigger(0,GJOY_BUTTON_1);
}
const GSvector2& Input::getVelocity()const
{
	GSvector2 vel(getHorizontal(),getVertical());
	return vel.normalize();
}
//êÖïΩ	
const float Input::getHorizontal()const
{
	float f = gsGetKeyState(GKEY_RIGHT) || gsGetJoyState(0,GJOY_RIGHT);
	f -= gsGetKeyState(GKEY_LEFT) || gsGetJoyState(0, GJOY_LEFT);
	return f;
}
//êÇíº
const float Input::getVertical()const
{
	float f = gsGetKeyState(GKEY_UP) || gsGetJoyState(0, GJOY_UP);
	f -= gsGetKeyState(GKEY_DOWN) || gsGetJoyState(0, GJOY_DOWN);
	return f;
}
const bool Input::getDebugResetTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_R);
}
const bool Input::getUpTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_UP) || !!gsGetJoyTrigger(0, GJOY_UP);
}
const bool Input::getDownTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_DOWN) || !!gsGetJoyTrigger(0, GJOY_DOWN);
}
const bool Input::getRightTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_RIGHT)||!!gsGetJoyTrigger(0, GJOY_RIGHT);
}
const bool Input::getLeftTrigger()const
{
	return !!gsGetKeyTrigger(GKEY_LEFT)||!!gsGetJoyTrigger(0, GJOY_LEFT);
}