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
	if (typeid(prot->getMove()) == typeid(Star_nomove)) return;//�����Ȃ����͂P�����������Ȃ�

	if (isStart() == false)return;//�ʏ�A���鐯����

	//���鐯
	if (prot->getType() == BREAKSTAR)
	{
		breakStart();
		return;
	}

	if ((int)timer.getTime() % 50 == 9){
		effectMediator.add("LightEffect", prot->getSPosi());
	}

	//�ʏ�̐�����
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
//���鐯�̍Đ���
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