#include "Stage.h"
#include "game.h"
#include "Device.h"
#include "CSVStream.h"
#include "GAMEOBJ_TYPE.h"
#include "Player.h"
#define  BLOCKSIZE 64.f
typedef std::shared_ptr<Factory> ObjFactory;

Stage::Stage(const std::string& csvname, Device& device)
:scroll(WINDOW_WIDTH, WINDOW_HEIGHT), timer(60, 60)
, starManager(scroll), device(device),
factory(ObjFactory(new GameObjectFactory(scroll, device)))
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
	starManager.initialize(&control);
	scroll.initialize();
	mapCreate();
	Stars_IsInScreen();
	isEnd = false;
	flag = CLEARFLAG::PLAYING;
}
void Stage::updata()
{
	starManager.updata();
	control.updata();
	timer.update();
	if (timer.isEnd())
	{
		flag = CLEARFLAG::GAMEOVER;
		isEnd = true;
	}

	if (control.StageClear(PLAYER))
	{
		timer.stop();
		flag = CLEARFLAG::CLEAR;
		if (control.isDeadPlayer())isEnd = true;
	}

}
void Stage::draw(const Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer, scroll);
	int t = timer.getTime() / FRAMETIME;
	renderer.DrawString(std::to_string(t), &GSvector2(50, 50), 50);
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
	//objcontrolに追加
	control.add_Star(starManager.getInScreenStars());
}