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

void GameObjControl::inisialize()
{
	objs.clear();
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
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
	std::sort(s, end,
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
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
	bool all_Noncollision = std::all_of(s, end,
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
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
	auto itrNewEnd = std::remove_if(s, end, [](GameObj_Ptr obj)->bool
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
void GameObjControl::draw(const Renderer& renderer, const Scroll& scroll)
{
	//drawOderSort();
	for each (GameObj_Ptr obj in objs)
	{
		obj->draw(renderer, scroll);
	}
}
void GameObjControl::finish()
{
	objs.clear();
}
bool GameObjControl::isDeadPlayer()
{
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
 	auto itr = std::find_if(s, end, [](GameObj_Ptr obj)->bool
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
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
	auto itr = std::find_if(s, end, [](GameObj_Ptr obj)->bool
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
	std::vector<GameObj_Ptr>::iterator s = objs.begin();
	std::vector<GameObj_Ptr>::iterator end = objs.end();
	GameObjs::iterator itr =
		std::find_if(s, end, [&](GameObj_Ptr obj)->bool
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