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
#include "GameObje_Include.h"
#include "IEffectMediator.h"
class Device;
class GameObjectFactory :public Factory<GameObj_Ptr,GAMEOBJ_TYPE>
{
public:
	GameObjectFactory(Scroll& scroll, Device& device,IEffectMediator* effectMediator);
	~GameObjectFactory();
	/**
	*@fn containerにGameobjectを登録
	*/
	void addContainer();
	/**
	*@fn containerに登録されているGameobjectのクローンを任意の位置で生成
	*/
	const GameObj_Ptr create(GAMEOBJ_TYPE type, const GSvector2& position)const;
private:
	std::map<GAMEOBJ_TYPE, GameObj_Ptr>container;
	Scroll& scroll;
	Device& device;
	IEffectMediator* effectMediator;
};

#endif
