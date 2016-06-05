#ifndef _GAMEOBJECTFACTORY_H_
#define _GAMEOBJECTFACTORY_H_
#include <map>
#include "GAMEOBJ_TYPE.h"
#include "Factory.h"

class GameObjectFactory:public Factory
{
public:
	GameObjectFactory(Scroll& scroll,Device& device);
	~GameObjectFactory();
	GameObj_Ptr createGameObject(GAMEOBJ_TYPE type, const GSvector2& position);
private:
	Scroll& scroll;
	Device& device;
};

#endif
