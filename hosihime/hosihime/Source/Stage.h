#ifndef _STAGE_H_
#define _STAGE_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "GameObjControl.h"
#include "Definition.h"
class Stage
{
public:
	Stage(const char* name);
	~Stage();
	void updata();
	void initialize();
	void draw(Renderer& renderer);
	void finish();
private:
	void mapCreate();
	void objCreate(int x, int y, Array2D<bool>* check);
	MapData mapdata;
	GameObjControl control;
};
#endif