#include "GameObjControl.h"
#include "Player.h"
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
	for each (GameObj_Ptr obj in objs)
	{
		if (obj->isSameType(STAR))
		{
			findPlayer()->setStar(obj.get());
		}
	}
	remove();
}
Player* GameObjControl::findPlayer()const
{
	for each(GameObj_Ptr obj in objs)
	{
		if (obj->isSameType(PLAYER))
		{
			return (Player*)obj.get();
		}
	}
	return 0;
}
void GameObjControl::remove()
{
	GameObjs::iterator itr = objs.begin();
	while (itr != objs.end())
	{
		if (itr->get()->getIsDead())
		{
			itr->get()->finish();
			itr = objs.erase(itr);
		}
		else
		{
			itr++;
		}
	}
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