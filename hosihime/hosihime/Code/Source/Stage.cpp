#include "Stage.h"
#include "game.h"
#include "Device.h"
#include "CSVStream.h"
#include "GAMEOBJ_TYPE.h"
#include "Player.h"
#include "NavigationUI.h"

typedef std::shared_ptr<Factory> ObjFactory;

Stage::Stage(const int& stageNo, Device& device)
	:scroll(WINDOW_WIDTH, WINDOW_HEIGHT, mapSize), device(device),
	timer(60, 60), control(), starManager(scroll, control),
	factory(ObjFactory(new GameObjectFactory(scroll, device))),
	navigation("nav1.bmp", control, scroll), mapSize(0,0),
	BLOCKSIZE(64.0f)
{
	CSVStream stream;
	stageNames[0] = "mapdata\\\\testmap.csv";
	stageNames[1] = "mapdata\\\\testmap.csv";
	stageNames[2] = "mapdata\\\\testmap.csv";
	//std::string name = "mapdata\\\\testmap" + std::to_string(stageNo) + ".csv";
	stream.input(&mapdata, stageNames[stageNo].c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	factory->addContainer();
	//device.getSound().PlaySE("GameMode_1.wav");
	timer.initialize();
	control.inisialize();
	starManager.initialize();
	scroll.initialize(GSvector2(0,0));
	mapCreate();
	Stars_IsInScreen();
	
	isEnd = false;
	navigation.initialize();
	flag = CLEARFLAG::PLAYING;
	mapSize = GSvector2(mapdata.getSize1(),mapdata.getSize0())*BLOCKSIZE;

	fade.initialize();
}
void Stage::updata()
{
	// 条件出してもっときれいに
	fade.updata();
	starManager.updata();
	control.updata();
	
	timer.update();
	if (timer.isEnd())
	{
		flag = CLEARFLAG::GAMEOVER;
		isEnd = true;
	}

	if (control.StageClear())
	{		
		timer.stop();
		flag = CLEARFLAG::CLEAR;
		if (!fade.getIsStart())
		{
			fade.start(GScolor(0, 0, 0, 0), GScolor(0,0,0, 1), 4);
		}
		
		if (fade.getIsEnd())
		{
			if (control.isDeadPlayer())isEnd = true;
		}		
	}
	else
	{
		navigation.updata();
	}
}
void Stage::draw(const Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer, scroll);
	int t = timer.getTime() / FRAMETIME;
	renderer.DrawString(std::to_string(t), &GSvector2(50, 50), 50);
	navigation.draw(renderer,scroll);
	fade.draw(renderer);
}
void Stage::finish()
{
	control.finish();
}

void Stage::saveScore(TimeScore& score)
{
	score.setScore(timer);
}

const bool Stage::getIsEnd()const
{
	return isEnd;
}

const CLEARFLAG Stage::getFlag() const
{
	return flag;
}

void Stage::objCreate(int x, int y)
{
	int data = mapdata(y, x);
	if (0 == data)
	{
		return;
	}	
	GSvector2 pos = GSvector2(x * BLOCKSIZE, y* BLOCKSIZE);
	control.add(factory->create(static_cast<GAMEOBJ_TYPE>(data), pos));	
}
void Stage::mapCreate()
{
	for (int y = 0,size=mapdata.getSize0(); y <size; ++y)
	{
		for (int x = 0, size1 = mapdata.getSize1(); x < size1; ++x)
		{
			objCreate(x, y);
		}
	}
	//スターの原型を全部生成
	starManager.createStarProt();
}

void Stage::Stars_IsInScreen()
{
	//画面内に入ってる星を見る
	starManager.addInScreenStars();
}