#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "GameObje_Include.h"
class Factory
{
public:
	GameObj_Ptr create(GAMEOBJ_TYPE type, const GSvector2& position)
	{
		return createGameObject(type,position);
	}
	virtual void addContainer() = 0;
private:
	virtual GameObj_Ptr createGameObject(GAMEOBJ_TYPE type, const GSvector2& position)=0;
};
#endif