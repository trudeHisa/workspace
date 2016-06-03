#ifndef STAR_PARADOLA_H_
#define STAR_PARADOLA_H_
#include "IStarMove.h"
//•ú•¨ü
class Star_paradola : public IStarMove
{
public:
	Star_paradola(float speed);
	Star_paradola(const Star_paradola& other);
	~Star_paradola();
	GSvector2 moving();
	IStarMove* clone();
private:
	float rot;
	float spd;
};

#endif