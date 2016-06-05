#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "GameObject.h"

#include <memory>
typedef std::shared_ptr<GameObject> GameObj_Ptr;
class Device;
class Factory
{
public:
	GameObj_Ptr create(GAMEOBJ_TYPE type, const GSvector2& position)
	{
		return createGameObject(type,position);
	}
private:
	virtual GameObj_Ptr createGameObject(GAMEOBJ_TYPE type, const GSvector2& position)=0;
};
#endif