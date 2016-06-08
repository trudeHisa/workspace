#ifndef STAR_SLASHDOWN_H_
#define STAR_SLASHDOWN_H_
#include "IStarMove.h"
//éŒÇﬂê¸
class Star_slashdown : public IStarMove
{
public:
	Star_slashdown(const GSvector2 &velocity);
	Star_slashdown(const Star_slashdown& other);
	~Star_slashdown();
	 GSvector2 moving();
	 IStarMove* clone();
	 int length();
private:
	GSvector2 velocity;
};

#endif