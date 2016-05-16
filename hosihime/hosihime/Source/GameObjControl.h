#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "GamaObject.h"
#include "StarManager.h"
#include "StarMediator.h"
#include <vector>
#include <memory>
#include "Definition.h"
typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::vector<GameObj_Ptr> GameObjs;
typedef GameObjs::iterator GameObjs_Itr;
class Player;
class GameObjControl :public StarMediator
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
	void add_Star(starsContainer& stars);
	void reqestClone(Star* starclone);
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