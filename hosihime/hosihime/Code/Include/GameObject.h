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
	//コンストラクタ要リファクタリング
	GameObject(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect, const GAMEOBJ_TYPE type);
	virtual ~GameObject();
	virtual void updata() = 0;	
	virtual void draw(const Renderer& renderer, const Scroll& scroll);
	virtual void initialize();
	virtual void finish();
	virtual void collision(const GameObject* obj) = 0;
	//全てのオブジェクトと当たっていないときに呼び出される
	virtual void nonCollision();

	virtual GameObject* clone(const GSvector2& position)=0;
	//オブジェクトと当たっているか？
	const bool isCollision(const GameObject* obj)const;

	const bool isInScreen(const Scroll& scroll)const;
public:
	/*
	減らしたい
	*/
	const bool getIsDead()const;
	const GAMEOBJ_TYPE getType()const;
	const GSvector2& getPosition()const;
	const GSvector2& getViewSize()const;
	const MyRectangle& getRect()const;
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