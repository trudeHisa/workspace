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
	void updata();
	void inisialize();
	/*
	オブジェクトのサイズを返す
	*/
	void add(GameObject* object);
	void draw(Renderer& renderer, const Scroll* scroll);
	void finish();
private:
	void allCollision();
	void collision(GameObj_Ptr obj1, GameObj_Ptr obj2);
	void sendStarsPlayer();
	void setStar(GameObj_Ptr obj);
	const bool GameObjControl::findPlayer(GameObjs_Itr::_Vector_const_iterator* player)const;
	void remove();
	GameObjs objs;
};
#endif