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
	/*wrap x‚ªlow‚Ü‚Å‰º‚ª‚é‚Æhight‚É,hight‚Ü‚Åã‚ª‚é‚Ælow‚É*/
	T wrap(T x, T low, T hight)
	{
		const T n = std::fmod(x - low, hight - low);
		return (n >= 0) ? (n + low) : (n + hight);
	}
	/*clamp x‚ªlow‚Ü‚Åã‚ª‚é‚Ælow‚É,hight‚Ü‚Åã‚ª‚é‚Æhight‚É*/
	T clamp(T x, T low, T hight)
	{
		return std::min<T>(std::max<T>(x, low), hight);
	}
	T degTorad(T deg)
	{
		T rad = deg*(PI / 180.0f);
		return rad;
	}
	T radToDeg(T rad)
	{
		return rad * 180.0f / PI;
	}

	const GSvector2 wrap(const GSvector2& value, const GSvector2& low, const GSvector2& hight)
	{
		GSvector2 res(0, 0);
		res.x = wrap(value.x, low.x, hight.x);
		res.y = wrap(value.y, low.y, hight.y);
		return res;
	}

	//Vector‚ÌƒNƒ‰ƒ“ƒv
	const GSvector2 clamp(const GSvector2& value, const GSvector2& low, const GSvector2& hight)
	{
		GSvector2 res(0, 0);
		gsVector2Maximize(&res, &value, &low);
		gsVector2Minimize(&res, &res, &hight);
		return res;
	}
};
#endif