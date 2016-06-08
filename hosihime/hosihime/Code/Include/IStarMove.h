#ifndef ISTARMOVE_H_
#define ISTARMOVE_H_
#include "game.h"
#include <memory>

class IStarMove
{
public:
	virtual GSvector2 moving() = 0;
	virtual IStarMove* clone() = 0;
	virtual int length() = 0;
};
typedef std::shared_ptr<IStarMove>StarMove_Ptr;
#endif