#ifndef _GAMEOBJCONTROL_H_
#define _GAMEOBJCONTROL_H_

#include "GamaObject.h"
#include <vector>
#include <memory>
#include "Definition.h"
typedef std::shared_ptr<GameObject> GameObj_Ptr;
typedef std::vector<GameObj_Ptr> GameObjs;

class GameObjControl
{
public:
	GameObjControl();
	~GameObjControl();
	void updata(MapData* mapdata);
	void inisialize();
	void add(GameObject* object);
	void draw(Renderer& renderer);
	void finish();
private:
	void remove();
	GameObjs objs;
};
#endif