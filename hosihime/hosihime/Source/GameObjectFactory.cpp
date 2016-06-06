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
	GSvector2 position(0,0);	
	const int length = 5;
	GameObject* objs[length] = 
	{
		new Respawn("rock2.bmp", MyRectangle(position, GSvector2(153, 153))),
		new Player("player.bmp", MyRectangle(position, GSvector2(64, 64)), &scroll, device),
		new ImMovable("rock.bmp", MyRectangle(position, GSvector2(158, 100)),PLANET),
		new ImMovable("start.bmp", MyRectangle(position, GSvector2(200, 126)), START),
		new ImMovable("goal.bmp", MyRectangle(position, GSvector2(317, 200)), GOAL)
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
GameObj_Ptr GameObjectFactory::createGameObject(GAMEOBJ_TYPE type, const GSvector2& position)
{
	return GameObj_Ptr(container.at(type)->clone(position));
}