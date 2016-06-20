#include "StarFactory.h"
#include <algorithm>
#include "GameObje_Include.h"
#include "../Include/BreakStar.h"
#include "../Include/Star_nomove.h"
#include <typeinfo>
StarFactory::StarFactory(Star* prot, float time, IMediator& mediator, IEffectMediator& effectMediator)
	:prot(prot), timer(time, time), mediator(mediator), effectMediator(effectMediator)
{
	create();
}
StarFactory::~StarFactory()
{
}
void StarFactory::update()
{
	//動かない星
	if (dynamic_cast<Star_nomove*>(prot->getMove()) != NULL)
	{
		if (star->getIsDead()==false) return;
		timer.update();
		if (timer.isEnd())
		{
			create();
			timer.initialize();
		}
	}
		
	if (isStart() == false)return;//通常、壊れる星共通

	//壊れる星
	if (prot->getType() == BREAKSTAR)
	{
		breakStart();
		return;
	}

	if ((int)timer.getTime() % 50 == 9){
		effectMediator.add("LightEffect", prot->getSPosi());
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
	GameObj_Ptr player = mediator.get(PLAYER);
	if (player == NULL) return false;
	if (gsVector2Distance(&prot->getSPosi(), &player->getPosition()) < prot->getHelth())
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