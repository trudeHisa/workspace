#include "Stage.h"
#include "CSVStream.h"
#include "game.h"

#include "Star.h"
#include "Player.h"
#include "Rock.h"
#include "Planet.h"
#include "Start.h"
#include "Goal.h"

#include "Star_cricle.h"
#include "Star_pendulum.h"
#include "Star_wave.h"
#include "Star_eight.h"
Stage::Stage(const std::string& csvname)
:scroll(&Point(WINDOW_WIDTH, WINDOW_HEIGHT)), timer(30,30)
, resTime(1,10)
{
	CSVStream stream;
	stream.input(&mapdata,csvname.c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	//resTime.initialize();
	timer.initialize();
	control.inisialize();
	starManager.initialize(&control);
	scroll.initialize();
	mapCreate();
	Stars_IsInScreen();
	isEnd = false;
}
void Stage::updata()
{
	starManager.StarResporn();
	control.updata();
	timer.update();
	resTime.update();
	/*if (resTime.isEnd())
	{
		//IStarMove* s[]=
		//{
			//new Star_circle(4),
		//};
		control.add(new Star("star.bmp", GSvector2(scroll.getMovingAmount(), 50), new Star_wave(GSvector2(1, 3), 3)));
		control.add(new Star("star.bmp", GSvector2(scroll.getMovingAmount(),100), new Star_wave(GSvector2(3, 3), 3)));
		control.add(new Star("star.bmp", GSvector2(scroll.getMovingAmount(), 350), new Star_wave(GSvector2(2, 3), 3)));
		resTime.initialize();
}*/
	if (timer.isEnd()||control.isDeadPlayer())
	{
		isEnd = true;
	}
}
void Stage::draw(Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer,&scroll);
	int t = timer.getTime();
	renderer.DrawString(std::to_string(t), &GSvector2(50, 50), 50);
}
void Stage::finish()
{
	control.finish();
}
bool Stage::getIsEnd()
{
	return isEnd;
}
void Stage::objCreate(int x, int y, Array2D<bool>* check)
{
	if ((*check)(y, x))
	{
		return;
	}
	Point size;
	switch (mapdata(y, x))
	{
	/*case STAR:
		size = Point(1, 1);//値は5を基準？ waveのGSvector2のyは0で
		control.add(new Star("star.bmp",GSvector2(x * BLOCKSIZE,y* BLOCKSIZE),new Star_wave(GSvector2(3,3),5)));
		break;*/
	case ROCK:
	   size = Point(4, 2);
			control.add(new Rock("rock.bmp",GSvector2(x * BLOCKSIZE,y* BLOCKSIZE)));
		break;
	case PLAYER:
		size = Point(1, 1); 
		control.add(new Player("player.bmp",GSvector2(x * BLOCKSIZE, y* BLOCKSIZE), &scroll));
		break;
	case PLANET:
		size = Point(1, 1);
		control.add(new Planet("planet.bmp", GSvector2(x * BLOCKSIZE, y* BLOCKSIZE)));
		break;
	case START:
		size = Point(5, 3);
		control.add(new Start("start.bmp", GSvector2(x * BLOCKSIZE, y* BLOCKSIZE)));
		break;
	case GOAL:
		size = Point(5, 3);
		control.add(new Goal("goal.bmp", GSvector2(x * BLOCKSIZE, y* BLOCKSIZE)));
		break;
			
	}
	
	
	for (int sy = 0; sy < size.y; sy++)
	{
		for (int sx = 0; sx < size.x; sx++)
		{
			(*check)(y + sy, x + sx) = true;
		}
	}
}
void Stage::mapCreate()
{
	Array2D<bool> check;
	check.setSize(mapdata.getSize0(), mapdata.getSize1());
	for (int y = 0; y < check.getSize0(); y++)
	{
		for (int x = 0; x < check.getSize1(); x++)
		{
			check(y, x) = false;
		}
	}
	for (int y = 0; y < mapdata.getSize0(); y++)
	{
		for (int x = 0; x < mapdata.getSize1(); x++)
		{
			objCreate(x,y,&check);
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