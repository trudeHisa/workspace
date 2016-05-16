#ifndef STAR_CRICLE_H_
#define STAR_CRICLE_H_
#include "IStarMove.h"
//‰~
class Star_circle : public IStarMove
{
public:
	Star_circle(float speed);
	~Star_circle();
	GSvector2 moving();
private:
	float rot;
	float spd;
};

#endif