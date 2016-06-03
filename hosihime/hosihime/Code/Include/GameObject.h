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
	GameObject(const std::string& textrue, const MyRectangle& rect,
		const GAMEOBJ_TYPE type);
	virtual ~GameObject();
	virtual void updata() = 0;
	virtual void draw(const Renderer& renderer, const Scroll& scroll);
	virtual void initialize();
	virtual void finish();
	//オブジェクトと当たっているか？
	const bool isCollision(const GameObject* obj)const;
	virtual void collision(const GameObject* obj)=0;
public:
	const bool getIsDead()const;
	//同じならtrue
	const bool isSameType(GAMEOBJ_TYPE _type)const;
protected:	
	std::string textrue;
	GAMEOBJ_TYPE type;
	MyRectangle rect;
	bool isDead;
	GSvector2 velocity;
};
#endif