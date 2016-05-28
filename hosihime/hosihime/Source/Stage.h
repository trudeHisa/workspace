#ifndef _STAGE_H_
#define _STAGE_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "GameObjControl.h"
#include "StarManager.h"
#include "Definition.h"
#include "Scroll.h"
#include "Array2D.h"
#include "Timer.h"
class Stage
{
public:
	Stage(const std::string& csvname);
	~Stage();
	void updata();
	void initialize();
	void draw(Renderer& renderer);
	void finish();
	bool getIsEnd();
private:
	void mapCreate();
	void objCreate(int x, int y, Array2D<bool>* check);
	Array2D<int> mapdata;
	void Stars_IsInScreen();
	GameObjControl control;
	StarManger starManager;
	Scroll scroll;
	int BLOCKSIZE = 64;
	Timer timer;
	Timer resTime;
	bool isEnd;
};
#endif