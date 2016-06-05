#ifndef _MYRECTANGLE_H_
#define _MYRECTANGLE_H_
#include "game.h"
//
class MyRectangle
{
public:
	MyRectangle(float left, float top, float width, float height);	
	MyRectangle(const GSvector2& position, const GSvector2& size);
	~MyRectangle();
	//点が矩形内にあるか
	const bool contains(const GSvector2* _position)const;
	//矩形同士が重なっているか
	const bool intersects(const MyRectangle* other)const;
	//平行移動
	void translate(const GSvector2& _position);
	//resetposition
	void resetPosition(const GSvector2& _position);

	//サイズ拡張
	void expand(const GSvector2& _size);

	const float getWidth()const;
	const float getHeight()const;
	const GSvector2& getPosition()const;
	const GSvector2& getSize()const;
private:
	GSvector2 position;//左上
	GSvector2 size;//幅、高さ
};
#endif