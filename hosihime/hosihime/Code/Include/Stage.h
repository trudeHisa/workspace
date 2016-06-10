#ifndef _STAGE_H_
#define _STAGE_H_

#include "Renderer.h"
#include "GameObjControl.h"
#include "StarManager.h"
#include "../Include/CLEARFLAG.h"
#include "Scroll.h"
#include "Array2D.h"
#include "Timer.h"
#include "TimeScore.h"
#include "GameObjectFactory.h"

#include "NavigationUI.h"
#include<memory>
class Device;


class Stage
{
public:
	Stage(const int& stageNo, Device& device);
	~Stage();
	void updata();
	void initialize();
	void draw(const Renderer& renderer);
	void finish();
	const bool getIsEnd()const;
	const CLEARFLAG getFlag() const;
	void saveScore(TimeScore& score);
private:
	void mapCreate();
	void objCreate(int x, int y);
	void Stars_IsInScreen();
private:
	bool isEnd;
	CLEARFLAG flag;
	Array2D<int> mapdata;	
	GameObjControl control;
	StarManger starManager;
	Scroll scroll;
	Timer timer;
	Device& device;
	std::shared_ptr<Factory> factory;
	std::string stageNames[3];
	NavigationUI navigation;
	GSvector2 mapSize;
	
	const float BLOCKSIZE;
};
#endif