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
	setStar();	
	remove(mapdata);
}
void GameObjControl::setStar()
{
	for each (GameObj_Ptr obj in objs)
	{
		if (obj->isSameType(STAR))
		{
			findPlayer()->setStar(obj.get());
		}
	}
}
Player* GameObjControl::findPlayer()const
{
	auto p = std::find_if(objs.begin(), objs.end(), [](GameObj_Ptr obj)
	{
		return obj->isSameType(PLAYER);
	});
	return(Player*)p->get();
}
void GameObjControl::remove(MapData* mapdata)
{
	auto itrNewEnd=std::remove_if(objs.begin(), objs.end(),[&](GameObj_Ptr obj)->bool
	{
		if (!obj->getIsDead())
		{
			return false;
		}
		obj->finish(mapdata);
		return true;
	});
	objs.erase(itrNewEnd,objs.end());
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
		obj->draw(renderer,scroll);
	}
}
void GameObjControl::finish()
{

}