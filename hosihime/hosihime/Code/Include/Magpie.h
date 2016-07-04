#ifndef _MAGPIE_H_
#define _MAGPIE_H_
#include "GameObject.h"
#include "AnimationTimer.h"
#include "Animation.h"
#include "IMediator.h"
#include "Timer.h"
class Magpie:public GameObject
{
public:
	Magpie(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		IMediator* objMediator,Device& device );
	~Magpie();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);
	GameObject* clone(const GSvector2& position);
	void setPlayerPosi(GSvector2* playerPosi);
	/*
	カササギが乗れる状況か？
	*/
	const bool isRide()const;
private:
	float speed;
	enum State
	{
		STANDBY, TAKEIN,SENDON
	};
	State state;
//	Timer timer;
	float t;
	IMediator* objMediator;
	float angle;
	GSvector2 targetPoint;
	Animation anim;
	AnimationTimer animTimer;
	std::string dir;

	Device& device;
};

#endif