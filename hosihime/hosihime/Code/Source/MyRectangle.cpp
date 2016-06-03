#include "MyRectangle.h"
//
MyRectangle::MyRectangle(float left, float top, float width, float height)
	:position(left,top), size(width,height)
{

}
MyRectangle::MyRectangle(const GSvector2& position, const GSvector2& size)
	: position(position), size(size)
{

}

MyRectangle::~MyRectangle()
{

}

//点が矩形内にあるか
const bool MyRectangle::contains(const GSvector2& _position)const
{
	return (position.x <= _position.x&&_position.x <= (position.x+size.x)) &&
		(position.y <= _position.y&&_position.y <=( position.y+size.y));
}
//矩形同士が重なっているか
const bool MyRectangle::intersects(const MyRectangle& other)const
{
	if (position.x > (other.position.x+other.size.x))return false;
	if ((position.x+size.x) < other.position.x)return false;
	if (position.y > (other.position.y+other.size.y))return false;
	if ((position.y+size.y) < other.position.y)return false;
	return true;
}
//平行移動
void MyRectangle::translate(const GSvector2& _position)
{
	position += _position;
}
void MyRectangle::resetPosition(const GSvector2& _position)
{
	position = _position;
}
//サイズ拡張
void MyRectangle::expand(const GSvector2& _size)
{
	size += _size;
}
const float MyRectangle::getWidth()const
{
	return size.x;
}
const float MyRectangle::getHeight()const
{
	return size.y;
}
const GSvector2& MyRectangle::getPosition()const
{
	return position;
}
const GSvector2& MyRectangle::getSize()const
{
	return size;
}