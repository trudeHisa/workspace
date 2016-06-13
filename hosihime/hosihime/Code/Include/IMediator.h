#ifndef _IMEDIATOR_H_
#define _IMEDIATOR_H_
#include "GameObje_Include.h"
#include <vector>
class IMediator
{
public:
	virtual ~IMediator(){}
	virtual void add(GameObj_Ptr obj) = 0;
	/**
	*�P��getter
	*/
	virtual GameObj_Ptr get(GAMEOBJ_TYPE type) = 0;
	/**
	*����getter
	*/
	virtual void gets(std::vector<GameObj_Ptr>* out, GAMEOBJ_TYPE type)= 0;
};

#endif