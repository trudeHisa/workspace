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
}
StarFactory::~StarFactory()
{
}
void StarFactory::update()
{
	if (typeid(prot->getMove()) == typeid(Star_nomove)) return;//動かない星は１個しか生成しない

	if (isStart() == false)return;//通常、壊れる星共通

	//壊れる星
	if (prot->getType() == BREAKSTAR)
	{
		breakStart();
		return;
	}

	//通常の星たち
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
//壊れる星の再生成
void StarFactory::breakCreate()
{
	if (timer.isEnd()){
		create();
		isbreakStart = false;
		timer.initialize();
	}
}
void StarFactory::breakStart()
{
	isbreakStart = static_cast<BreakStar*>(star.get())->getIsDead() ? true : isbreakStart;

	if (isbreakStart)
	{
		timer.update();
	}

	breakCreate();
}