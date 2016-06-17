#include "GameObjectFactory.h"

#include "Star.h"
#include "Player.h"
#include "Respawn.h"
#include "ImMovable.h"
#include "Magpie.h"
#include "Signboard.h"

#include "Device.h"
#include "Scroll.h"

GameObjectFactory::GameObjectFactory(
	Scroll& scroll, Device& device,
	IMediator* objMediator, IEffectMediator* effectMediator)
	:scroll(scroll), device(device), container(),
	objMediator(objMediator),effectMediator(effectMediator)
{
}

GameObjectFactory::~GameObjectFactory()
{
}
void GameObjectFactory::addContainer()
{
	GSvector2 zero(0,0);
	const int length = 16;
	GameObject* objs[length] = 
	{
		new Respawn("rock.bmp", zero, GSvector2(158, 100), MyRectangle(GSvector2(23, 16), GSvector2(113, 28))),
		new Player("player.bmp", zero, GSvector2(64, 64), MyRectangle(GSvector2(20, 50), GSvector2(30, 14)), &scroll, device,effectMediator),
		new ImMovable("rock2_2.bmp", zero, GSvector2(117, 79), MyRectangle(zero, GSvector2(117, 79)), PLANET),
		new ImMovable("start.bmp", zero, GSvector2(200, 126), MyRectangle(GSvector2(40, 20), GSvector2(128, 20)), START),
		new ImMovable("goal.bmp", zero, GSvector2(317, 200), MyRectangle(GSvector2(50, 40), GSvector2(226, 26)), GOAL),
		new Magpie("magpie.bmp", zero, GSvector2(128, 128), MyRectangle(GSvector2(0, 0), GSvector2(128, 128)), objMediator),
		new ImMovable("magpieEnd.bmp", zero, GSvector2(128, 128), MyRectangle(GSvector2(0, 0), GSvector2(128, 128)),MAGPIE_ENDSPOT),

		new Signboard("nav1.bmp", GSvector2(100, 100), GSvector2(64, 64), SIGNBOARD_R),
		new Signboard("nav1.bmp", GSvector2(200, 100), GSvector2(64, 64), SIGNBOARD_L),
		new Signboard("nav1.bmp", GSvector2(300, 100), GSvector2(64, 64), SIGNBOARD_U),
		new Signboard("nav1.bmp", GSvector2(100, 100), GSvector2(64, 64), SIGNBOARD_D),

		new Signboard("nav1.bmp", GSvector2(200, 100), GSvector2(64, 64), SIGNBOARD_RU),
		new Signboard("nav1.bmp", GSvector2(300, 100), GSvector2(64, 64), SIGNBOARD_RD),

		new Signboard("nav1.bmp", GSvector2(100, 100), GSvector2(64, 64), SIGNBOARD_LD),
		new Signboard("nav1.bmp", GSvector2(200, 100), GSvector2(64, 64), SIGNBOARD_LU),

	};
	GAMEOBJ_TYPE types[length]=
	{
		RESPAWN,
		PLAYER,
		PLANET,
		START,
		GOAL,
		MAGPIE,
		MAGPIE_ENDSPOT,

		SIGNBOARD_R,
		SIGNBOARD_L,
		SIGNBOARD_U,
		SIGNBOARD_D,

		SIGNBOARD_RU,
		SIGNBOARD_RD,
		SIGNBOARD_LD,
		SIGNBOARD_LU

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