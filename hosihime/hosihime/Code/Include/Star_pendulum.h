#ifndef STAR_PENDULUM_H_
#define STAR_PENDULUM_H_
#include "IStarMove.h"
//�U��q
class Star_pendulum : public IStarMove
{
public:
	Star_pendulum(float speed,float shwidth);
	Star_pendulum(const Star_pendulum& other);
	~Star_pendulum();
	GSvector2 moving();
	IStarMove* clone();
private:
	float rot;
	float spd;
	float sindw;
};

#endif