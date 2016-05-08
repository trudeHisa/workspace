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
	scroll.initialize();
	mapCreate();
}
void Stage::updata()
{
	control.updata(&mapdata);
}
void Stage::draw(Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer,&scroll);
	/*for (int y = -1; y < mapdata.getSize0()-1; y++)
	{
		for (int x = -1; x < mapdata.getSize1()-1; x++)
		{
			if (scroll.isInsideWindow(x *  BLOCKSIZE,BLOCKSIZE))
			{
				std::string tex = "space";
				GScolor c = GScolor(1,1,1,1);
				switch (mapdata(y, x))
				{
				case GAMEOBJ_TYPE::SPACE:
					break;
				case GAMEOBJ_TYPE::STAR:
					tex = "star";
					c = GScolor(0,1, 0, 1);
					break;
				case GAMEOBJ_TYPE::PLAYER:
					tex = "player";
					c = GScolor(1,0,0, 1);
					break;
				case GAMEOBJ_TYPE::ROCK:
					tex = "rock";
					break;
				default:
					tex = "other";
					break;
				}
				renderer.DrawString(tex, &GSvector2(x *  BLOCKSIZE-scroll.getMovingAmount(), y *  BLOCKSIZE), 10,&c);
			}			
		}
	}*/
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
	case STAR:
		size = control.add(new Star("star.bmp", &GSvector2(x * BLOCKSIZE,y* BLOCKSIZE)));
		break;
	case ROCK:
		size = control.add(new Rock("rock.bmp", &GSvector2(x * BLOCKSIZE,y* BLOCKSIZE)));
		break;
	case PLAYER:
		size = control.add(new Player("player.bmp", &GSvector2(x * BLOCKSIZE,y* BLOCKSIZE), &scroll));
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