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
	//�_����`���ɂ��邩
	const bool contains(const GSvector2* _position)const;
	//��`���m���d�Ȃ��Ă��邩
	const bool intersects(const MyRectangle* other)const;
	//���s�ړ�
	void translate(const GSvector2& _position);
	//resetposition
	void resetPosition(const GSvector2& _position);

	//�T�C�Y�g��
	void expand(const GSvector2& _size);

	const float getWidth()const;
	const float getHeight()const;
	const GSvector2& getPosition()const;
	const GSvector2& getSize()const;
private:
	GSvector2 position;//����
	GSvector2 size;//���A����
};
#endif