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
	const bool getIsDead()const;
protected:
	virtual void nextPosition(GSvector2* pos) = 0;//ˆÚ“®Œã‚ÌˆÊ’u‚ð•Ô‚·
	virtual const bool isNextMove(const MapData* mapdata);//ˆÚ“®‚Å‚«‚é‚©

	void mapUpdata(MapData* mapdata, const Point* point, GAMEOBJ_TYPE oldPostype);	
	void castLocation(const GSvector2* pos,Point* loc);
	std::string textrue;
	bool isDead;
	Point location;
	GSvector2 position;
	GAMEOBJ_TYPE type;
	Point size;
};
#endif