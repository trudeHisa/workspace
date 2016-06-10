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
	/*wrap xがlowまで下がるとhightに,hightまで上がるとlowに*/
	T wrap(T x, T low, T hight)
	{
		const T n = std::fmod(x - low, hight - low);
		return (n >= 0) ? (n + low) : (n + hight);
	}
	/*clamp xがlowまで上がるとlowに,hightまで上がるとhightに*/
	T clamp(T x, T low, T hight)
	{
		return std::min<T>(std::max<T>(x, low), hight);
	}
	T degTorad(T deg)
	{
		T rad=deg*(PI/180.0f);
		return rad;
	}
	//Vectorのクランプ
	GSvector2 clamp(const GSvector2& value, const GSvector2& low, const GSvector2& hight)
	{
		GSvector2 res(0,0);
		gsVector2Maximize(&res, &value, &low);
		gsVector2Minimize(&res, &value, &hight);
		return res;
	}
};
#endif