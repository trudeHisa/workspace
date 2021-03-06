#include "Stage.h"
#include "CSVStream.h"
#include "game.h"
#include "Star.h"
#include "Player.h"
#include "Respawn.h"
#include "ImMovable.h"
#include "Input.h"
#define  BLOCKSIZE 64.f

Stage::Stage(const std::string& csvname,const Input& input)
	:scroll(WINDOW_WIDTH, WINDOW_HEIGHT), timer(60,60)
	, input(input), starManager(scroll)
{
	CSVStream stream;
	stream.input(&mapdata, csvname.c_str());
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
	starManager.updata();
	control.updata();
	timer.update();
	if (timer.isEnd() || control.isDeadPlayer())
	{
		
		timer.stop();
		isEnd = true;
	}
}
void Stage::draw(Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer, &scroll);
	int t = timer.getTime()/FRAMETIME;
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
	GSvector2 pos = GSvector2(x * BLOCKSIZE, y* BLOCKSIZE);
	GSvector2 fsize;
	switch (mapdata(y, x))
	{
	case RESPAWN:
		size = Point(2, 2);
		fsize = GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);
		control.add(new Respawn("rock.bmp", MyRectangle(pos, fsize)));
		break;
	case PLAYER:
		size = Point(1, 1);
		fsize = GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);
		control.add(new Player("player.bmp", MyRectangle(pos, fsize), &scroll,input));
		break;
	case PLANET:
		size = Point(2,2);
		fsize = GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);
		control.add(new ImMovable("planet.bmp", MyRectangle(pos, fsize), PLANET));
		break;
	case START:
		size = Point(3, 3);
		fsize = GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);
		control.add(new ImMovable("start.bmp", MyRectangle(pos, fsize), START));
		break;
	case GOAL:
		size = Point(3, 3);
		fsize = GSvector2(size.x*BLOCKSIZE, size.y*BLOCKSIZE);
		control.add(new ImMovable("goal.bmp", MyRectangle(pos, fsize), GOAL));
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
			objCreate(x, y, &check);
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