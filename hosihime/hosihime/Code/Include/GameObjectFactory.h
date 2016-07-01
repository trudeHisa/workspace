/**
*@file GameObjectFactory
*@brief Gameobject�̐���
*@author matuo
*@data 2016/6/05
*/
#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_
#include <unordered_map>
#include "GAMEOBJ_TYPE.h"
#include "Factory.h"
#include "GameObje_Include.h"
#include "IEffectMediator.h"
#include "IMediator.h"
class Device;
class GameObjectFactory :public Factory<GameObj_Ptr,GAMEOBJ_TYPE>
{
public:
	GameObjectFactory(Scroll& scroll, Device& device,
		IMediator* objMediator,IEffectMediator* effectMediator);
	~GameObjectFactory();
	/**
	*@fn container��Gameobject��o�^
	*/
	void addContainer();
	/**
	*@fn container�ɓo�^����Ă���Gameobject�̃N���[����C�ӂ̈ʒu�Ő���
	*/
	const GameObj_Ptr create(GAMEOBJ_TYPE type, const GSvector2& position)const;
private:
	std::unordered_map<GAMEOBJ_TYPE, GameObj_Ptr>container;
	Scroll& scroll;
	Device& device;
	IMediator* objMediator;
	IEffectMediator* effectMediator;
};

#endif
