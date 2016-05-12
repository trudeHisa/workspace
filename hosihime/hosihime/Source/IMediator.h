#ifndef _IMEDIATOR_H_
#define _IMEDIATOR_H_
#include "Point.h"
#include "GamaObject.h"
class IMediator
{
public:
	virtual const Point& add(GameObject* object) = 0;
	virtual GameObject* getGameObject(const Point& loc,GAMEOBJ_TYPE type)=0;
};

#endif