/**
*@file GameObjectFactory
*@brief Gameobject�̐���
*@author matuo
*@data 2016/6/05
*/
#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_
#include <map>
#include "GAMEOBJ_TYPE.h"
#include "Factory.h"

class GameObjectFactory :public Factory
{
public:
	GameObjectFactory(Scroll& scroll, Device& device);
	~GameObjectFactory();
	/**
	*@fn container��Gameobject��o�^
	*/
	void addContainer();
	/**
	*@fn container�ɓo�^����Ă���Gameobject�̃N���[����C�ӂ̈ʒu�Ő���
	*/
	GameObj_Ptr createGameObject(GAMEOBJ_TYPE type, const GSvector2& position);
private:
	std::map<GAMEOBJ_TYPE, GameObj_Ptr>container;
	Scroll& scroll;
	Device& device;
};

#endif
