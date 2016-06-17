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
	Star* prot;//å¥å^
	Star_Ptr star;//íºëOÇ…ê∂ê¨ÇµÇΩêØ(âÛÇÍÇÈêØóp)
	bool isbreakStart;
	IMediator& mediator;
	Timer timer;
};
#endif