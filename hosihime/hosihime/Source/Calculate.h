#ifndef _CALCULATE_H_
#define _CALCULATE_H_

#include <iostream>
#include <algorithm>
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
};
#endif