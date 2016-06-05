#include "GameObjectFactory.h"

#include "Star.h"
#include "Player.h"
#include "Respawn.h"
#include "ImMovable.h"

#include "Device.h"
#include "Scroll.h"
GameObjectFactory::GameObjectFactory(Scroll& scroll, Device& device)
	:scroll(scroll), device(device)
{
}

GameObjectFactory::~GameObjectFactory()
{
}
GameObj_Ptr GameObjectFactory::createGameObject(GAMEOBJ_TYPE type, const GSvector2& position)
{
	switch (type)
	{
	case RESPAWN:
		return GameObj_Ptr(new Respawn("rock2.bmp", MyRectangle(position, GSvector2(153, 153))));
	case PLAYER:
		return GameObj_Ptr(new Player("player.bmp", MyRectangle(position, GSvector2(64, 64)),&scroll, device));
	case PLANET:
		return GameObj_Ptr(new ImMovable("rock.bmp", MyRectangle(position, GSvector2(158, 100)), type));
	case START:
		return GameObj_Ptr(new ImMovable("start.bmp", MyRectangle(position, GSvector2(200, 126)), type));
	case GOAL:
		return GameObj_Ptr(new ImMovable("goal.bmp", MyRectangle(position, GSvector2(317, 200)), type));
	default:
		return NULL;
	}
}