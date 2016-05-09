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
	//’¼ü
	void LinePattern1();//‰E‰º‚É—‚¿‚é
	void LinePattern2();//¶‰º‚É—‚¿‚é
	//•ú•¨ü
	void LinePattern3();//‰E‰º
	void LinePattern4();//¶‰º

	//‰~‰^“®
	void LinePattern5();
	//ƒuƒ‰ƒ“ƒR‚İ‚½‚¢‚È“®‚«
	void LinePattern6();
	//”gü
	void LinePattern7();
	float ang, movx, movy, spd, sindw, rot = 0;
	bool collision(int nextPosType);
	void nextVelocity(GSvector2* _velocity,float* angle);
	float angle;
};
#endif