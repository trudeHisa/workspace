#include "GameObjControl.h"
#include "Player.h"
#include <algorithm>
#include "../Include/Timer.h"
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
//	remove();
}
void GameObjControl::allCollision()
{
	for each (GameObj_Ptr obj1 in objs)
	{
		for each (GameObj_Ptr obj2 in objs)
		{
			collision(obj1, obj2);
		}
	}
}
void GameObjControl::collision(GameObj_Ptr obj1, GameObj_Ptr obj2)
{
	if (!obj1->isCollision(obj2.get()))
	{
		return;
	}
	obj1->collision(obj2.get());
	obj2->collision(obj1.get());
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
void GameObjControl::add(GameObj_Ptr object)
{
	object->initialize();
	objs.emplace_back(object);
}


//‰æ–Ê“à‚É“ü‚Á‚Ä‚¢‚é¯‚ğobjControl‚É“n‚·
void GameObjControl::add_Star(Stars_inScreen& stars)
{
	for each(Star_Ptr star in stars)
	{
		add((GameObj_Ptr)star);
	}
}

void GameObjControl::draw(const Renderer& renderer, const Scroll& scroll)
{
	for each (GameObj_Ptr obj in objs)
	{
		obj->draw(renderer, scroll);
	}
}
bool GameObjControl::isDeadPlayer()
{
	auto itr = std::find_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)->bool
	{
		return obj->isSameType(PLAYER);
	});
	if (itr == objs.end())
	{
		return true;

	}
	return false;
}

void GameObjControl::finish()
{
	
}

void GameObjControl::reqestClone(Star_Ptr starclone)
{
	//‰ŠúˆÊ’u‚ª‰æ–Ê“à‚È‚ç
	//if ()
	add((GameObj_Ptr)starclone);
}