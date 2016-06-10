#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "StarManager.h"
#include "IMediator.h"
#include <vector>
#include "GameObje_Include.h"
typedef std::vector<GameObj_Ptr> GameObjs;
class Player;
class Timer;
class GameObjControl :public IMediator
{
public:
	GameObjControl();
	~GameObjControl();
	void updata();
	void inisialize();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	bool isDeadPlayer();
	bool StageClear();
public:
	void add(GameObj_Ptr obj);
	GameObj_Ptr get(GAMEOBJ_TYPE type);
	void gets(std::vector<GameObj_Ptr>* out, GAMEOBJ_TYPE type);
private:
	void drawOderSort();
	void allCollision();
	const bool isCollision(GameObj_Ptr obj1, GameObj_Ptr obj2);
	void collision(GameObj_Ptr obj1);
	void remove();
private:
	GameObjs objs;
};
#endif