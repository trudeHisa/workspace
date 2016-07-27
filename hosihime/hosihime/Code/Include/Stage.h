#ifndef _STAGE_H_
#define _STAGE_H_

#include<memory>

#include "Renderer.h"
#include "GameObjControl.h"
#include "StarManager.h"
#include "CLEARFLAG.h"
#include "Scroll.h"
#include "Array2D.h"
#include "Timer.h"
#include "TimeScore.h"
#include "GameObjectFactory.h"
#include "Fade.h"

#include "EffectController.h"

#include "StarFade.h"
class Device;
typedef std::shared_ptr<Factory<GameObj_Ptr,GAMEOBJ_TYPE>> ObjFactory;

class Stage
{
public:
	Stage(const int& stageNo, Device& device,StarFade& starFade);
	~Stage();
	void updata();
	void initialize();
	void draw(const Renderer& renderer);
	void finish();
	const bool getisEnd()const;
	const CLEARFLAG getFlag() const;
	void saveScore(TimeScore& score);
private:
	void mapCreate();
	void objCreate(int x, int y);
	void Stars_IsInScreen();
private:
	float timerFontSize;
	bool tFS_Plus;
	bool isEnd;
	CLEARFLAG flag;
	Array2D<int> mapdata;	
	GameObjControl control;
	StarManger starManager;
	Scroll scroll;
	Timer timer;
	Device& device;
	ObjFactory factory;
	GSvector2 mapSize;
	Fade fadeOut;
	Fade fadeIn;

	bool pcount;

	EffectsFactory effectFactory;
	EffectController effectController;

	StarFade& starFade;
	Timer fadeTimer;

	const float BLOCKSIZE;
	const unsigned int stageNo;
};
#endif