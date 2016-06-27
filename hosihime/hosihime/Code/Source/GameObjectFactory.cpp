#include "GameObjectFactory.h"

#include "Star.h"
#include "Player.h"
#include "Respawn.h"
#include "ImMovable.h"
#include "Magpie.h"
#include "Signboard.h"
#include "Hikoboshi.h"
#include "Device.h"
#include "Scroll.h"

GameObjectFactory::GameObjectFactory(
	Scroll& scroll, Device& device,
	IMediator* objMediator, IEffectMediator* effectMediator)
	:scroll(scroll), device(device), container(),
	objMediator(objMediator), effectMediator(effectMediator)
{
}

GameObjectFactory::~GameObjectFactory()
{
}
void GameObjectFactory::addContainer()
{
	GSvector2 zero(0, 0);
	const int length = 17;
	GSvector2 navSize(45,100);
	GameObject* objs[length] =
	{
		/*           画像名,　　位置(原型),見た目のサイズ(基本画像サイズ),　位置からの当たり判定位置と横縦幅 */
		new Respawn("respawn.bmp", zero, GSvector2(94, 88), MyRectangle(GSvector2(11, 11), GSvector2(85, 0))),
		new Player("orihime.bmp", zero, GSvector2(64, 64), MyRectangle(GSvector2(20, 50), GSvector2(30, 14)), &scroll, device, effectMediator),
		new ImMovable("meteo.bmp", zero, GSvector2(44, 44), MyRectangle(zero, GSvector2(44, 44)), PLANET),
		new ImMovable("start.bmp", zero, GSvector2(200, 100), MyRectangle(GSvector2(30, 15), GSvector2(180, 30)), START),
		new ImMovable("goal.bmp", zero, GSvector2(200, 100), MyRectangle(GSvector2(30, 15), GSvector2(180, 30)), GOAL),
		new Magpie("magpie.bmp", zero, GSvector2(128, 128), MyRectangle(GSvector2(0, 0), GSvector2(128, 128)), objMediator),
		new ImMovable("magpieEnd.bmp", zero, GSvector2(94, 88), MyRectangle(GSvector2(11, 11), GSvector2(85, 23)), MAGPIE_ENDSPOT),

		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_R),
		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_L),
		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_U),
		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_D),

		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_RU),
		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_RD),

		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_LD),
		new Signboard("nav.bmp", zero, navSize, SIGNBOARD_LU),

		new ImMovable("sasa.bmp", zero, GSvector2(96, 128), MyRectangle(zero, zero), SASA),
		new Hikoboshi("hikobosi.bmp",zero,GSvector2(64,64),MyRectangle(zero,GSvector2(64,64)))
	};
	GAMEOBJ_TYPE types[length] =
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
		SIGNBOARD_LU,
		SASA,
		HIKOBOSHI
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