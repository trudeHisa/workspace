/**
*@file GameObjectFactory
*@brief Gameobjectの生成
*@author matuo
*@data 2016/6/05
*/
#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_
#include <map>
#include "GAMEOBJ_TYPE.h"
#include "Factory.h"
class Device;
class GameObjectFactory :public Factory
{
public:
	GameObjectFactory(Scroll& scroll, Device& device);
	~GameObjectFactory();
	/**
	*@fn containerにGameobjectを登録
	*/
	void addContainer();
	/**
	*@fn containerに登録されているGameobjectのクローンを任意の位置で生成
	*/
	GameObj_Ptr createGameObject(GAMEOBJ_TYPE type, const GSvector2& position);
private:
	std::map<GAMEOBJ_TYPE, GameObj_Ptr>container;
	Scroll& scroll;
	Device& device;
};

#endif
