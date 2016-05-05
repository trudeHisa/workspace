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

class GameObject
{
public:
	GameObject(const std::string& textrue,const Point* size,
		const GAMEOBJ_TYPE type,const GSvector2* position);
	~GameObject();
	virtual void updata(MapData* mapdata) = 0;
	virtual void draw(Renderer& renderer);
	virtual void initialize();
	virtual void finish();
	const Point getSize()const;
	const GAMEOBJ_TYPE getType()const;
	const bool getIsDead()const;
	const Point getLocation()const;
	const GSvector2 getPosition()const;
protected:
	/*
	移動後の位置オブジェクトがある場合
	返す値は移動できるかできないかを返す
	*/
	virtual bool nextAction(int nextPosType)=0;
	virtual void nextPosition(GSvector2* pos) = 0;//移動後の位置を返す
	virtual const bool isNextMove(const MapData* mapdata);//移動できるか
	//サイズ分マップデータに代入する関数
	void mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type);
	void mapUpdata(MapData* mapdata, const Point* point, GAMEOBJ_TYPE oldPostype);	
	void castLocation(const GSvector2* pos,Point* loc);
	const bool isInSideMap(const MapData* mapdata, const Point* point)const;//マップ内ならtrue

protected:
	std::string textrue;
	bool isDead;
	Point location;
	GSvector2 position;
	GAMEOBJ_TYPE type;
	Point size;
};
#endif