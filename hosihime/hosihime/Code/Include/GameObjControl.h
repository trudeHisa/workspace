#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "StarManager.h"
#include "StarMediator.h"
#include <vector>
#include "GameObje_Include.h"
typedef std::vector<GameObj_Ptr> GameObjs;
class Player;
class Timer;
class GameObjControl :public StarMediator
{
public:
	GameObjControl();
	~GameObjControl();
	void updata();
	void inisialize();
	void add(GameObj_Ptr object);
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	void add_Star(Stars_inScreen& stars);
	void reqestClone(Star_Ptr starclone);
	bool isDeadPlayer();
	bool StageClear(GAMEOBJ_TYPE _type);
private:
	void allCollision();
	void collision(GameObj_Ptr obj1);//, GameObj_Ptr obj2);
	void remove();
private:
	GameObjs objs;
};
#endif