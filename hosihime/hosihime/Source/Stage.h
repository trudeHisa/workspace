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
#include "TimeScore.h"
#include "GameObjectFactory.h"
#include<memory>
class Device;
class Stage
{
public:
	Stage(const std::string& csvname, Device& device);
	~Stage();
	void updata();
	void initialize();
	void draw(const Renderer& renderer);
	void finish();
	bool getIsEnd();
	void saveScore(TimeScore& score);
private:
	void mapCreate();
	void objCreate(int x, int y);
	void Stars_IsInScreen();
private:
	int BLOCKSIZE = 64;
	bool isEnd;
	Array2D<int> mapdata;	
	GameObjControl control;
	StarManger starManager;
	Scroll scroll;
	Timer timer;
	Device& device;
	std::shared_ptr<Factory> factory;
};
#endif