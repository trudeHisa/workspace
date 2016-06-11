#include "GameObjControl.h"
#include "Player.h"
#include <algorithm>
#include "Timer.h"
GameObjControl::GameObjControl()
{

}
GameObjControl::~GameObjControl()
{

}
void GameObjControl::updata()
{
	remove();
	for each (GameObj_Ptr obj in objs)
	{
		obj->updata();
	}
	allCollision();
}
void GameObjControl::drawOderSort()
{
	std::sort(objs.begin(), objs.end(),
		[](const GameObj_Ptr& obj1, const GameObj_Ptr& obj2)
	{
		return obj1->getType() < obj2->getType();
	});
}
void GameObjControl::allCollision()
{
	for each (GameObj_Ptr obj in objs)
	{
		collision(obj);
	}
}
const bool GameObjControl::isCollision(GameObj_Ptr obj1, GameObj_Ptr obj2)
{
	if (obj1 == obj2)
	{
		return true;
	}
	if (obj1->isCollision(obj2.get()))
	{
		obj1->collision(obj2.get());
		obj2->collision(obj1.get());
		return false;
	}
	return true;
}
void GameObjControl::collision(GameObj_Ptr obj1)
{
	bool all_Noncollision = std::all_of(objs.begin(), objs.end(),
		[&](GameObj_Ptr obj2)
	{
		return isCollision(obj1, obj2);
	});
	if (!all_Noncollision)
	{
		return;
	}
	obj1->nonCollision();
}
void GameObjControl::remove()
{
	auto itrNewEnd = std::remove_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)->bool
	{
		if (!obj->getIsDead())
		{
			return false;
		}
		obj->finish();
		return true;
	});
	objs.erase(itrNewEnd, objs.end());
}
void GameObjControl::inisialize()
{
	objs.clear();
}

void GameObjControl::draw(const Renderer& renderer, const Scroll& scroll)
{
	drawOderSort();
	for each (GameObj_Ptr obj in objs)
	{
		obj->draw(renderer, scroll);
	}
}
void GameObjControl::finish()
{

}
bool GameObjControl::isDeadPlayer()
{
	auto itr = std::find_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)->bool
	{
		return obj->getType() == PLAYER;
	});
	if (itr == objs.end())
	{
		return true;
	}
	return false;
}

bool GameObjControl::StageClear()
{
	auto itr = std::find_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)->bool
	{
		return obj->getType()== PLAYER;
	});
	if (itr == objs.end())
	{
		return true;
	}
	GameObj_Ptr g = *itr;
	return static_cast<Player*>(g.get())->getIsClear();
}
void GameObjControl::add(GameObj_Ptr obj)
{
	obj->initialize();
	objs.emplace_back(obj);
}
GameObj_Ptr GameObjControl::get(GAMEOBJ_TYPE type)
{
	GameObjs::iterator itr =
		std::find_if(objs.begin(), objs.end(), [&](GameObj_Ptr obj)->bool
	{
		return obj->getType() == type;
	});
	if (itr == objs.end())
	{
		return NULL;
	}
	return *itr;
}
void GameObjControl::gets(std::vector<GameObj_Ptr>* out, GAMEOBJ_TYPE type)
{
	int size = out->size();
	for each (GameObj_Ptr obj in objs)
	{
		if (obj->getType() == type)
		{
			out->emplace_back(obj);
		}
	}
}