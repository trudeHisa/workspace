/**
*@file GameObjectFactory
*@brief Gameobject‚Ì¶¬
*@author matuo
*@data 2016/6/05
*/
#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_
#include <map>
#include "GAMEOBJ_TYPE.h"
#include "Factory.h"
#include "GameObje_Include.h"
class Device;
class GameObjectFactory :public Factory<GameObj_Ptr,GAMEOBJ_TYPE>
{
public:
	GameObjectFactory(Scroll& scroll, Device& device);
	~GameObjectFactory();
	/**
	*@fn container‚ÉGameobject‚ğ“o˜^
	*/
	void addContainer();
	/**
	*@fn container‚É“o˜^‚³‚ê‚Ä‚¢‚éGameobject‚ÌƒNƒ[ƒ“‚ğ”CˆÓ‚ÌˆÊ’u‚Å¶¬
	*/
	const GameObj_Ptr create(GAMEOBJ_TYPE type, const GSvector2& position)const;
private:
	std::map<GAMEOBJ_TYPE, GameObj_Ptr>container;
	Scroll& scroll;
	Device& device;
};

#endif
