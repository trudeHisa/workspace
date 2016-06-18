#include "Stage.h"
#include "game.h"
#include "Device.h"
#include "CSVStream.h"
#include "GAMEOBJ_TYPE.h"
#include "Player.h"
#include "EffectFactory.h"

Stage::Stage(const int& stageNo, Device& device)
	:stageNo(stageNo),
	scroll(WINDOW_WIDTH, WINDOW_HEIGHT, mapSize, stageNo),
	device(device), timer(0, 0), BLOCKSIZE(64.0f),
	control(),
	effectFactory(EffectsFactory(new EffectFactory())),
	effectController(effectFactory),
	mapSize(0, 0),
	factory(ObjFactory(new GameObjectFactory(scroll, device, &control, &effectController))),
	starManager(stageNo, scroll, control, effectController,device),
	fadeIn(), fadeOut()
{
	CSVStream stream;
	std::string name = "mapdata\\\\testmap" + std::to_string(stageNo) + ".csv";
	stream.input(&mapdata, name.c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	device.getSound().PlaySE("gamemode0.wav");

	factory->addContainer();
	effectFactory->addContainer();

	//device.getSound().PlaySE("GameMode_1.wav");
	timer.initialize();
	control.inisialize();
	starManager.initialize();
	scroll.initialize(GSvector2(0, 0));
	mapCreate();
	Stars_IsInScreen();

	isEnd = false;
	flag = CLEARFLAG::PLAYING;
	mapSize = GSvector2(mapdata.getSize1(), mapdata.getSize0())*BLOCKSIZE;

	fadeOut.initialize();
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 3.f);

	effectController.initialize();
}
void Stage::updata()
{
	
	// 条件出してもっときれいに
	fadeIn.updata();
	fadeOut.updata();

	starManager.updata();
	control.updata();
	effectController.update();
	if (!fadeIn.getIsEnd())
	{
		return;
	}	
	
	timer.update();
	/*if (timer.isEnd())
	{
	flag = CLEARFLAG::GAMEOVER;
	isEnd = true;
	}*/

	if (control.StageClear())
	{
		timer.stop();
		flag = CLEARFLAG::CLEAR;
		if (!fadeOut.getIsStart())
		{
			fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 2);
		}
		isEnd = fadeOut.getIsEnd();
	}
}
void Stage::draw(const Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer, scroll);
	int t = timer.getTime() / FRAMETIME;
	renderer.DrawString(std::to_string(t), 
		&GSvector2(50, 50), 70,&GScolor(1,1,0,1),GS_FONT_ITALIC,"メイリオ");

	effectController.draw(renderer, scroll);

	fadeOut.draw(renderer);
	fadeIn.draw(renderer);
}
void Stage::finish()
{
	control.finish();
	device.getSound().StopSE("gamemode0.wav");
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
	for (int y = 0, size = mapdata.getSize0(); y < size; ++y)
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