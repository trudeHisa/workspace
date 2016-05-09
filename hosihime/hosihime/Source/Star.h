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
	//直線
	void LinePattern1();//右下に落ちる
	void LinePattern2();//左下に落ちる
	//放物線
	void LinePattern3();//右下
	void LinePattern4();//左下

	//円運動
	void LinePattern5();
	//ブランコみたいな動き
	void LinePattern6();
	//波線
	void LinePattern7();
	float ang, movx, movy, spd, sindw, rot = 0;
	bool collision(int nextPosType);
	void nextVelocity(GSvector2* _velocity,float* angle);
	float angle;
};
#endif