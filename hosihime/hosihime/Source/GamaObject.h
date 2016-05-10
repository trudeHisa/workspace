/*
GameObject.h
*/
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "Point.h"
#include <string>
#include "Definition.h"
#include "Scroll.h"
class GameObject
{
public:
	GameObject(const std::string& textrue,const Point* size,
		const GAMEOBJ_TYPE type,const GSvector2* position);
	~GameObject();
	virtual void updata(MapData* mapdata) = 0;
	virtual void draw(Renderer& renderer,const Scroll* scroll);
	virtual void initialize();
	virtual void finish(MapData* mapdata);
public:
	const Point getSize()const;
	const bool getIsDead()const;
	//同じならtrue
	const bool isSameLocation(const Point& _location)const;
	const bool isSameType(GAMEOBJ_TYPE _type)const;
private:
	//mapdataの更新
	void mapUpdata(MapData* mapdata, const Point* point, GAMEOBJ_TYPE oldPostype);
	//マップ内ならtrue
	const bool isInDataMap(const MapData* mapdata, const Point* point)const;
protected:	
	//移動後の位置オブジェクトがある場合返す値は移動できるかできないかを返す	
	virtual bool collision(int nextPosType)=0;
	//サイズ分マップデータに代入する関数
	void mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type);	
	//posをBLOCKSIZEで割りlocに代入
	void castLocation(const GSvector2* pos,Point* loc);
	//移動処理
	void move(MapData* mapdata,GAMEOBJ_TYPE oldPostype);	
	//オブジェクトと当たっているか？
	const bool isCollision(const MapData* mapdata,const Point* nextLocation);	
	//移動できるか
	const bool isNextMove(const MapData* mapdata, const GSvector2* nextVelcity);
	/*
	描画用に位置を変える
	trueなら描画,falseなら描画しない
	*/
	bool forDrawPosition(GSvector2* _position, const Scroll* scroll);
protected:
	std::string textrue;
	bool isDead;
	Point location;
	GSvector2 position;
	GAMEOBJ_TYPE type;
	Point size;
	GSvector2 velocity;
};
#endif