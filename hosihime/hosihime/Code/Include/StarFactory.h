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
	void breakStart();
	void breakCreate();
private:
	Star* prot;//原型
	Star_Ptr star;//直前に生成した星(壊れる星用)
	float breakTime;
	bool isbreakStart;
	IMediator& mediator;
	Timer timer;
};
#endif