#ifndef _MAGPIE_H_
#define _MAGPIE_H_
#include "GameObject.h"

#include "IMediator.h"
#include "Timer.h"
class Magpie:public GameObject
{
public:
	Magpie(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		IMediator* objMediator);
	~Magpie();
	void initialize();
	void updata();
	void collision(const GameObject* obj);

	GameObject* clone(const GSvector2& position);

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
	Timer timer;
	IMediator* objMediator;
	float angle;
	GSvector2 targetPoint;
};

#endif