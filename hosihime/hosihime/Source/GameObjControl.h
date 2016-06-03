#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "GameObject.h"
#include "StarManager.h"
#include "StarMediator.h"
#include <vector>
#include <memory>

typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::vector<GameObj_Ptr> GameObjs;
class Player;
class GameObjControl :public StarMediator
{
public:
	GameObjControl();
	~GameObjControl();
	void updata();
	void inisialize();
	void add(GameObject* object);
	void draw(Renderer& renderer, const Scroll* scroll);
	void finish();
	void add_Star(Stars_inScreen& stars);
	void reqestClone(Star* starclone);
	bool isDeadPlayer();
private:
	void allCollision();
	void collision(GameObj_Ptr obj1, GameObj_Ptr obj2);
	void remove();
private:
	GameObjs objs;
};
#endif