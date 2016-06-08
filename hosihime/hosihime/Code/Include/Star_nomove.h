#ifndef _STAR_NOMOVE_H_
#define _STAR_NOMOVE_H_
#include "IStarMove.h"

class Star_nomove:public IStarMove
{
public:
	Star_nomove();
	~Star_nomove();
	GSvector2 moving();
	IStarMove* clone();
	int length();
private:

};
#endif