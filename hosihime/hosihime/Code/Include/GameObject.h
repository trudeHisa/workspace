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
	//オブジェクトと当たっているか？
	const bool isCollision(const GameObject* obj)const;
public:
	const bool getIsDead()const;
	//同じならtrue
	const bool isSameType(GAMEOBJ_TYPE _type)const;
protected:	
	std::string textrue;//テクスチャ名
	GAMEOBJ_TYPE type;//オブジェクトのタイプ
	MyRectangle rect;//当たり判定
	GSvector2 position;//位置
	GSvector2 viewSize;//見た目のサイズ
	bool isDead;
	GSvector2 velocity;//毎フレームごとの速度
};
#endif