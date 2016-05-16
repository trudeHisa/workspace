#ifndef _MYRECTANGLE_H_
#define _MYRECTANGLE_H_
#include "game.h"
//
class MyRectangle
{
public:
	MyRectangle(float left, float top, float right, float bottom);
	~MyRectangle();
	MyRectangle(const GSvector2& min, const GSvector2& max);
	//点が矩形内にあるか
	const bool contains(const GSvector2& position)const;
	//矩形同士が重なっているか
	const bool intersects(const MyRectangle& other)const;
	//平行移動
	void translate(const GSvector2& position);
	//サイズ拡張
	void expand(const GSvector2& size);
	const float getWidth()const;
	const float getHeight()const;
	const GSvector2& getMin()const;
	const GSvector2& getMax()const;
private:
	GSvector2 min_;//左上
	GSvector2 max_;//右下
};
#endif