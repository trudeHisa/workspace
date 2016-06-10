#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#include <iostream>
#include <algorithm>
#include <gslib.h>
#define PI 3.14159265
template<class T>
class Calculate
{
public:
	Calculate(){}
	/*wrap x��low�܂ŉ������hight��,hight�܂ŏオ���low��*/
	T wrap(T x, T low, T hight)
	{
		const T n = std::fmod(x - low, hight - low);
		return (n >= 0) ? (n + low) : (n + hight);
	}
	/*clamp x��low�܂ŏオ���low��,hight�܂ŏオ���hight��*/
	T clamp(T x, T low, T hight)
	{
		return std::min<T>(std::max<T>(x, low), hight);
	}
	T degTorad(T deg)
	{
		T rad=deg*(PI/180.0f);
		return rad;
	}
	//Vector�̃N�����v
	GSvector2 clamp(const GSvector2& value, const GSvector2& low, const GSvector2& hight)
	{
		GSvector2 res(0,0);
		gsVector2Maximize(&res, &value, &low);
		gsVector2Minimize(&res, &value, &hight);
		return res;
	}
};
#endif