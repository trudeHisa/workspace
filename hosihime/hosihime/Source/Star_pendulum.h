#ifndef STAR_PENDULUM_H_
#define STAR_PENDULUM_H_
#include "IStarMove.h"
//êUÇËéq
class Star_pendulum : public IStarMove
{
public:
	Star_pendulum(float speed,float shwidth);
	~Star_pendulum();
	GSvector2 moving();
private:
	float rot;
	float spd;
	float sindw;
};

#endif