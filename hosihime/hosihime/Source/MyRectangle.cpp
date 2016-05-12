#include "MyRectangle.h"

MyRectangle::MyRectangle(float left, float top, float right, float bottom)
	:min_(left,top), max_(right,bottom)
{

}
MyRectangle::MyRectangle(const GSvector2& min, const GSvector2& max)
	: min_(min), max_(max)
{

}
MyRectangle::~MyRectangle()
{

}

//�_����`���ɂ��邩
const bool MyRectangle::contains(const GSvector2& position)const
{
	return (min_.x <= position.x&&position.x <= max_.x) &&
		(min_.y <= position.y&&position.y <= max_.y);
}
//��`���m���d�Ȃ��Ă��邩
const bool MyRectangle::intersects(const MyRectangle& other)const
{
	if (min_.x > other.max_.x)return false;
	if (max_.x < other.min_.x)return false;
	if (min_.y > other.max_.y)return false;
	if (max_.y < other.min_.y)return false;
	return true;
}
//���s�ړ�
MyRectangle MyRectangle::translate(const GSvector2& position)const
{
	return MyRectangle(min_ + position, max_ + position);
}
//�T�C�Y�g��
MyRectangle MyRectangle::expand(const GSvector2& size)const
{
	return MyRectangle(min_ - size, max_ + size);
}
const float MyRectangle::getWidth()const
{
	return max_.x - min_.x;
}
const float MyRectangle::getHeight()const
{
	return max_.y - min_.y;
}
const GSvector2& MyRectangle::getMin()const
{
	return min_;
}
const GSvector2& MyRectangle::getMax()const
{
	return max_;
}