#ifndef STAR_PARADOLA_H_
#define STAR_PARADOLA_H_
#include "IStarMove.h"
//������
class Star_paradola : public IStarMove
{
public:
	Star_paradola(float speed);
	~Star_paradola();
	GSvector2 moving();
private:
	float rot;
	float spd;
};

#endif