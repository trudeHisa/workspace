#include "StarFactory.h"
#include <algorithm>
#include "GameObje_Include.h"

StarFactory::StarFactory(Star* prot, float time, IMediator& mediator)
:star(prot), timer(0, time), mediator(mediator)
{
}
StarFactory::~StarFactory()
{
}
void StarFactory::update()
{
	if (isStart() == false)return;

	timer.update();
	if (timer.isEnd())
	{
		create();
		timer.initialize();
	}
}

bool StarFactory::isStart()
{
	if (gsVector2Distance(&star->getSPosi(), &mediator.get(PLAYER)->getPosition()) < star->getHelth())
		return true;

	return false;

}
void StarFactory::create()
{
	GameObj_Ptr s = GameObj_Ptr(star->clone());
	mediator.add(s);
}
