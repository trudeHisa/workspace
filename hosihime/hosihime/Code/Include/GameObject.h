/*
GameObject.h
*/
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "Point.h"
#include <string>

#include "Scroll.h"
#include "MyRectangle.h"
class GameObject
{
public:
	GameObject(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect, const GAMEOBJ_TYPE type);
	virtual ~GameObject();
	virtual void updata() = 0;	
	virtual void draw(const Renderer& renderer, const Scroll& scroll);
	virtual void initialize();
	virtual void finish();
	virtual void collision(const GameObject* obj) = 0;

	virtual GameObject* clone(const GSvector2& position)=0;
	//�I�u�W�F�N�g�Ɠ������Ă��邩�H
	const bool isCollision(const GameObject* obj)const;
public:
	const bool getIsDead()const;
	//�����Ȃ�true
	const bool isSameType(GAMEOBJ_TYPE _type)const;
protected:	
	std::string textrue;//�e�N�X�`����
	GAMEOBJ_TYPE type;//�I�u�W�F�N�g�̃^�C�v
	MyRectangle rect;//�����蔻��
	GSvector2 position;//�ʒu
	GSvector2 viewSize;//�����ڂ̃T�C�Y
	bool isDead;
	GSvector2 velocity;//���t���[�����Ƃ̑��x
};
#endif