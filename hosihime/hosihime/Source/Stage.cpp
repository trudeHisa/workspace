#include "Stage.h"
#include "CSVStream.h"
#include "Star.h"
#include "Player.h"
#include "Rock.h"
#include "game.h"
Stage::Stage(const std::string& csvname)
	:scroll(&Point(WINDOW_WIDTH,WINDOW_HEIGHT))
{
	CSVStream stream;
	stream.input(&mapdata,csvname.c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	control.inisialize();
	starManager.initialize(&control);
	scroll.initialize();
	mapCreate();
	Stars_IsInScreen();
}
void Stage::updata()
{
	starManager.StarResporn();
	control.updata();
	//Stars_IsInScreen();
}
void Stage::draw(Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer,&scroll);
}
void Stage::finish()
{
	control.finish();
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
		//size = Point(1, 1);
		 //control.add(new Star("star.bmp",GSvector2(x * BLOCKSIZE,y* BLOCKSIZE)));
		break;*/
	case ROCK:
		size = Point(2, 1);
			control.add(new Rock("rock.bmp",GSvector2(x * BLOCKSIZE,y* BLOCKSIZE)));
		break;
	case PLAYER:
		size = Point(1, 1); 
		control.add(new Player("player.bmp",GSvector2(x * BLOCKSIZE, y* BLOCKSIZE), &scroll));
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