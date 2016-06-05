#ifndef _STARMEDIATOR_H_
#define _STARMEDIATOR_H_
#include "GameObje_Include.h"

class StarMediator
{
public:
	~StarMediator(){}
	virtual void reqestClone(Star_Ptr starclone) = 0;
};

#endif