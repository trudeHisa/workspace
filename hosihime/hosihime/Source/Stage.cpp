#include "Stage.h"
#include "CSVStream.h"
#include "Star.h"
#include "Rock.h"
Stage::Stage(const char* name)
{
	CSVStream stream;
	stream.input(&mapdata, name);
}

Stage::~Stage()
{
}
void Stage::initialize()
{
	control.inisialize();
	mapCreate();
}
void Stage::updata()
{
	control.updata(&mapdata);
}
void Stage::draw(Renderer& renderer)
{
	control.draw(renderer);
	for (int y = 0; y < mapdata.getSize0(); y++)
	{
		for (int x = 0; x < mapdata.getSize1(); x++)
		{
			std::string tex = "space";
			switch (mapdata(y, x))
			{
			case GAMEOBJ_TYPE::SPACE:
				break;
			case GAMEOBJ_TYPE::STAR:
				tex = "star";
				break;
			case GAMEOBJ_TYPE::PLAYER:
				tex = "player";
				break;
			case GAMEOBJ_TYPE::ROCK:
				tex = "rock";
				break;
			default:
				tex = "other";
				break;
			}
			renderer.DrawString(tex, &GSvector2(x *  BLOCKSIZE, y *  BLOCKSIZE), 10);
		}
	}
}
void Stage::finish()
{
	control.finish();
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
			switch (mapdata(y, x))
			{
			case STAR:
				control.add(new Star("star.bmp", &GSvector2(x * BLOCKSIZE, y * BLOCKSIZE)));
				break;
			case ROCK:
				control.add(new Rock("rock.bmp", &GSvector2(x * BLOCKSIZE, y * BLOCKSIZE)));
				break;
			}
		}
	}
}