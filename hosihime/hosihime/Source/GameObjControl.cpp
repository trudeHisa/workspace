#include "GameObjControl.h"
#include "Player.h"
#include <algorithm>

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
void GameObjControl::add(GameObject* object)
{
	object->initialize();
	objs.push_back(GameObj_Ptr(object));
}


//‰æ–Ê“à‚É“ü‚Á‚Ä‚¢‚é¯‚ğobjControl‚É“n‚·
void GameObjControl::add_Star(starsContainer& stars)
{
	for each(Star* star in stars)
	{
		add(star);
	}
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

void GameObjControl::reqestClone(Star* starclone)
{
	//‰ŠúˆÊ’u‚ª‰æ–Ê“à‚È‚ç
	//if ()
	add(starclone);
}