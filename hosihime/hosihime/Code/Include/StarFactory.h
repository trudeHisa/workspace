#ifndef _STARFACTORY_H_
#define _STARFACTORY_H_

#include "IMediator.h"
#include "Timer.h"

class StarFactory 
{
public:
	StarFactory(Star* prot,float time,IMediator& mediator);
	~StarFactory();
	void update();
	bool isStart();
private:
	void create();
private:
	Star* star;
	IMediator& mediator;
	Timer timer;
};
#endif