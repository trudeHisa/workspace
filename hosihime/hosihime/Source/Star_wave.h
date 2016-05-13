#ifndef STAR_WAVE_H_
#define STAR_WAVE_H_
#include "IStarMove.h"

class Star_wave : public IStarMove
{
public:
	Star_wave(GSvector2 vel, float shwidth);
	~Star_wave();
	GSvector2 moving();
private:
	GSvector2 velocity;
	float rot;
	float spd;
	float sindw;
};

#endif