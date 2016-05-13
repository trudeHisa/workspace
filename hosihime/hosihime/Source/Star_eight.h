#ifndef STAR_EIGHT_H_
#define STAR_EIGHT_H_
#include "IStarMove.h"
//8‚ÌŽš
class Star_eight : public IStarMove
{
public:
	Star_eight(float speed,float shwidth);
	~Star_eight();
	GSvector2 moving();
private:
	float rot;
	float spd;
	float sindw;
};
#endif