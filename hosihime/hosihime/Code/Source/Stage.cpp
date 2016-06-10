#include "Stage.h"
#include "game.h"
#include "Device.h"
#include "CSVStream.h"
#include "GAMEOBJ_TYPE.h"

#define  BLOCKSIZE 64.f
Stage::Stage(const std::string& csvname, Device& device)
	:scroll(WINDOW_WIDTH, WINDOW_HEIGHT), timer(60,60),
	control(),starManager(scroll,control), device(device),
	factory(std::shared_ptr<Factory>(new GameObjectFactory(scroll, device))),
	navigation("nav1.bmp", control, scroll)
{
	CSVStream stream;
	stream.input(&mapdata, csvname.c_str());
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
	scroll.initialize();
	mapCreate();
	Stars_IsInScreen();
	
	isEnd = false;
	navigation.initialize();
}
void Stage::updata()
{
	starManager.updata();
	control.updata();
	navigation.updata();
	timer.update();
	if (timer.isEnd() || control.isDeadPlayer())
	{		
		timer.stop();
		isEnd = true;
	}
}
void Stage::draw(const Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer,scroll);
	int t = timer.getTime()/FRAMETIME;
	renderer.DrawString(std::to_string(t), &GSvector2(50, 50), 50);
	navigation.draw(renderer,scroll);
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
	for (int y = 0; y < mapdata.getSize0(); y++)
	{
		for (int x = 0; x < mapdata.getSize1(); x++)
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