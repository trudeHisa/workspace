#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#include <iostream>
#include <algorithm>
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
};
#endif