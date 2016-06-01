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

//�_����`���ɂ��邩
const bool MyRectangle::contains(const GSvector2& _position)const
{
	return (position.x <= _position.x&&_position.x <= (position.x+size.x)) &&
		(position.y <= _position.y&&_position.y <=( position.y+size.y));
}
//��`���m���d�Ȃ��Ă��邩
const bool MyRectangle::intersects(const MyRectangle& other)const
{
	if (position.x > (other.position.x+other.size.x))return false;
	if ((position.x+size.x) < other.position.x)return false;
	if (position.y > (other.position.y+other.size.y))return false;
	if ((position.y+size.y) < other.position.y)return false;
	return true;
}
//���s�ړ�
void MyRectangle::translate(const GSvector2& _position)
{
	position += _position;
}
void MyRectangle::resetPosition(const GSvector2& _position)
{
	position = _position;
}
//�T�C�Y�g��
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