#ifndef STAR_WAVE_H_
#define STAR_WAVE_H_
#include "IStarMove.h"
//”g
class Star_wave : public IStarMove
{
public:
	Star_wave(GSvector2 vel, float shwidth);
	Star_wave(const Star_wave& other);
	~Star_wave();
	GSvector2 moving();
	IStarMove* clone();
	int length();
private:
	GSvector2 velocity;
	float rot;
	float spd;
	float sindw;
};

#endif