#include "GameObjControl.h"
#include "Player.h"
#include <algorithm>

GameObjControl::GameObjControl()
{

}
GameObjControl::~GameObjControl()
{

}
void GameObjControl::updata(MapData* mapdata)
{
	for each (GameObj_Ptr obj in objs)
	{
		obj->updata(mapdata);
	}
	sendStarsPlayer();
	remove(mapdata);
}
void GameObjControl::sendStarsPlayer()
{
	for each (GameObj_Ptr obj in objs)
	{
		setStar(obj);
	}
}
void GameObjControl::setStar(GameObj_Ptr obj)
{
	if (!obj->isSameType(STAR))
	{
		return;
	}
	GameObjs_Itr::_Vector_const_iterator player;
	if (!findPlayer(&player))
	{
		return;
	}
	((Player*)player->get())->setStar(obj.get());
}
const bool GameObjControl::findPlayer(GameObjs_Itr::_Vector_const_iterator* player)const
{
	auto itr = std::find_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)
	{
		return obj->isSameType(PLAYER);
	});
	if (itr == objs.end())
	{
		return false;
	}
	*player = itr;
	return true;
}
void GameObjControl::remove(MapData* mapdata)
{
	auto itrNewEnd = std::remove_if(objs.begin(), objs.end(), [&](GameObj_Ptr obj)->bool
	{
		if (!obj->getIsDead())
		{
			return false;
		}
		obj->finish(mapdata);
		return true;
	});
	objs.erase(itrNewEnd, objs.end());
}
void GameObjControl::inisialize()
{
	objs.clear();
}
const Point& GameObjControl::add(GameObject* object)
{
	object->initialize();
	objs.push_back(GameObj_Ptr(object));
	return object->getSize();
}
void GameObjControl::draw(Renderer& renderer, const Scroll* scroll)
{
	for each (GameObj_Ptr obj in objs)
	{
		obj->draw(renderer, scroll);
	}
}
void GameObjControl::finish()
{

}