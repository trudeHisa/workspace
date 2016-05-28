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
{
	CSVStream stream;
	stream.input(&mapdata,csvname.c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	timer.initialize();
	control.inisialize();
	scroll.initialize();
	mapCreate();
	isEnd = false;
}
void Stage::updata()
{
	control.updata();
	timer.update();
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
	case STAR:
		size = Point(1, 1);																			//ílÇÕ5ÇäÓèÄÅH waveÇÃGSvector2ÇÃyÇÕ0Ç≈
		control.add(new Star("star.bmp",GSvector2(x * BLOCKSIZE,y* BLOCKSIZE),new Star_circle(4)));
		break;
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
}