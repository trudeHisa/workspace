#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "GamaObject.h"
#include <vector>
#include <memory>
#include "Definition.h"
typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::vector<GameObj_Ptr> GameObjs;
class Player;
class GameObjControl
{
public:
	GameObjControl();
	~GameObjControl();
	void updata(MapData* mapdata);
	void inisialize();
	/*
	オブジェクトのサイズを返す
	*/
	const Point& add(GameObject* object);
	void draw(Renderer& renderer, const Scroll* scroll);
	void finish();
private:
	Player* findPlayer() const;
	void remove();
	GameObjs objs;
};
#endif