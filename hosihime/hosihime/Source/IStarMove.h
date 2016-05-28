#ifndef ISTARMOVE_H_
#define ISTARMOVE_H_
#include "game.h"

class IStarMove
{
public:
	virtual GSvector2 moving() = 0;
};

#endif