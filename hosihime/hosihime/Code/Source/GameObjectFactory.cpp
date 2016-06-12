#include "GameObjectFactory.h"

#include "Star.h"
#include "Player.h"
#include "Respawn.h"
#include "ImMovable.h"

#include "Device.h"
#include "Scroll.h"
GameObjectFactory::GameObjectFactory(Scroll& scroll, Device& device)
	:scroll(scroll), device(device), container()
{
}

GameObjectFactory::~GameObjectFactory()
{
}
void GameObjectFactory::addContainer()
{
	GSvector2 zero(0,0);
	const int length = 5;
	GameObject* objs[length] = 
	{
		new Respawn("rock.bmp", zero, GSvector2(158, 100), MyRectangle(GSvector2(23, 16), GSvector2(113, 28))),
		new Player("player.bmp", zero,GSvector2(64,64),MyRectangle(GSvector2(20,50), GSvector2(30,14)), &scroll, device),
		new ImMovable("rock2_2.bmp", zero, GSvector2(117, 79), MyRectangle(zero, GSvector2(117, 79) ), PLANET),
		new ImMovable("start.bmp", zero, GSvector2(200,126), MyRectangle(GSvector2(40, 20), GSvector2(128, 20)), START),
		new ImMovable("goal.bmp", zero, GSvector2(317,200), MyRectangle(GSvector2(50, 40), GSvector2(226, 26)), GOAL)
	};
	GAMEOBJ_TYPE types[length]=
	{
		RESPAWN,
		PLAYER,
		PLANET,
		START,
		GOAL
	};
	for (int i = 0; i < length; i++)
	{
		GameObj_Ptr obj = GameObj_Ptr(objs[i]);
		container.insert(std::pair<GAMEOBJ_TYPE, GameObj_Ptr>(types[i], obj));
	}
}
const GameObj_Ptr GameObjectFactory::create(GAMEOBJ_TYPE type, const GSvector2& position)const
{
	return GameObj_Ptr(container.at(type)->clone(position));
}