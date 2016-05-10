#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "GamaObject.h"
#include <vector>
#include <memory>
#include "Definition.h"
typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::vector<GameObj_Ptr> GameObjs;
typedef GameObjs::iterator GameObjs_Itr;
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
	void sendStarsPlayer();
	void setStar(GameObj_Ptr obj);
	const bool GameObjControl::findPlayer(GameObjs_Itr::_Vector_const_iterator* player)const;
	void remove(MapData* mapdata);
	GameObjs objs;
};
#endif