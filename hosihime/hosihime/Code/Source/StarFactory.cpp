#include "StarFactory.h"
#include <algorithm>
#include "GameObje_Include.h"
#include "../Include/BreakStar.h"
#include "../Include/Star_nomove.h"
#include <typeinfo>
StarFactory::StarFactory(Star* prot, float time, IMediator& mediator)
:prot(prot), timer(time, time), mediator(mediator)
{
	create();
	breakTime = time * 60;
}
StarFactory::~StarFactory()
{
}
void StarFactory::update()
{
	if (typeid(prot->getMove()) == typeid(Star_nomove)) return;//ìÆÇ©Ç»Ç¢êØÇÕÇPå¬ÇµÇ©ê∂ê¨ÇµÇ»Ç¢

	if (isStart() == false)return;//í èÌÅAâÛÇÍÇÈêØã§í 

	//âÛÇÍÇÈêØ
	if (prot->getType() == BREAKSTAR)
	{
		breakStart();
		return;
	}

	//í èÌÇÃêØÇΩÇø
	timer.update();
	if (timer.isEnd())
	{
		create();
		timer.initialize();
	}
}

bool StarFactory::isStart()
{
	if (gsVector2Distance(&prot->getSPosi(), &mediator.get(PLAYER)->getPosition()) < prot->getHelth())
		return true;

	return false;
}
void StarFactory::create()
{
	star = static_cast<Star_Ptr>(prot->clone());
	mediator.add(star);
}
//âÛÇÍÇÈêØÇÃçƒê∂ê¨
void StarFactory::breakCreate()
{
	if (breakTime < 0){
		create();
		isbreakStart = false;
		breakTime = timer.getDefTime() * 60;
	}
}
void StarFactory::breakStart()
{
	isbreakStart = static_cast<BreakStar*>(star.get())->getIsDead() ? true : isbreakStart;

	if (isbreakStart)
	{
		breakTime -= gsFrameTimerGetTime();
	}

	breakCreate();
}