#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
class Star:public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2* position);
	~Star();
	 void updata(MapData* mapdata);	
	 void playerPickUp(GSvector2* pos);
private:
	bool nextAction(int nextPosType);
	void nextVelocity(GSvector2* _velocity,float* angle);
	float angle;
};
#endif