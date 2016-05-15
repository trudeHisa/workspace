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
	//�_����`���ɂ��邩
	const bool contains(const GSvector2& position)const;
	//��`���m���d�Ȃ��Ă��邩
	const bool intersects(const MyRectangle& other)const;
	//���s�ړ�
	void translate(const GSvector2& position);
	//�T�C�Y�g��
	void expand(const GSvector2& size);
	const float getWidth()const;
	const float getHeight()const;
	const GSvector2& getMin()const;
	const GSvector2& getMax()const;
private:
	GSvector2 min_;//����
	GSvector2 max_;//�E��
};
#endif