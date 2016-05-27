#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
#include "StarMediator.h"
class Star :public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2 position);
	~Star();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void pickUp(GSvector2* vel);
	Star* clone();
	void finish();
private:
	GSvector2 startPosi;
	//直線
	void LinePattern1(GSvector2* _velocity);//右下に落ちる
	void LinePattern2(GSvector2* _velocity);//左下に落ちる
	//放物線
	void LinePattern3(GSvector2* _velocity, float* rot);//右下
	void LinePattern4(GSvector2* _velocity, float* rot);//左下

	//円運動
	void LinePattern5(GSvector2* _velocity, float* rot);
	//ブランコみたいな動き
	void LinePattern6(GSvector2* _velocity, float* rot);
	//波線
	void LinePattern7(GSvector2* _velocity, float* rot);
	float ang, spd, sindw, rot = 0;
};
#endif