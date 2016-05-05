#include "GameObjControl.h"
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
	remove();
}
void GameObjControl::remove()
{
	GameObjs::iterator itr = objs.begin();
	while (itr != objs.end())
	{
		if (itr->get()->getIsDead())
		{
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
void GameObjControl::add(GameObject* object)
{
	object->initialize();
	objs.push_back(GameObj_Ptr(object));
}
void GameObjControl::draw(Renderer& renderer)
{
	for each (GameObj_Ptr obj in objs)
	{
		obj->draw(renderer);
	}
}
void GameObjControl::finish()
{

}