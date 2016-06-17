#include "StarManager.h"
#include <algorithm>

#include "IMediator.h"

#include "Star_cricle.h"
#include "Star_eight.h"
#include "Star_parabola.h"
#include "Star_pendulum.h"
#include "Star_slashdown.h"
#include "Star_wave.h"
#include "Star_nomove.h"

#include "StarDataStream.h"

#include "BreakStar.h"
#include "BurnStar.h"

#include "STARTYPE.h"

StarManger::StarManger(Scroll& _scroll, IMediator& mediator, IEffectMediator& effectMediator)
:scroll(_scroll), mediator(mediator), effectMediator(effectMediator)
{
}
StarManger::~StarManger()
{
}
void StarManger::initialize()
{
	stars.clear();
}
IStarMove* StarManger::createMove(const std::vector<std::string>& param,float index)
{
	int type = stoi(param[index]);
	switch (type)
	{
	case CRICLE:
		return new Star_circle(stof(param[index+1]));
	case EIGHT:
		return new Star_eight(stof(param[index + 1]), stof(param[index + 2]));
	case PARABOLA:
		return new Star_paradola(stof(param[index + 1]));
	case PENDULAM:
		return new Star_pendulum(stof(param[index + 1]), stof(param[index + 2]));
	case SLASHDOWN:
		return new Star_slashdown(GSvector2(stof(param[index + 1]), stof(param[index + 2])));
	case WAVE:
		return new Star_wave(GSvector2(stof(param[index + 1]), stof(param[index + 2])), stof(param[index + 3]));
	case NOMOVE:
		return new Star_nomove();
	default:
		return NULL;
	}
}
MyRectangle StarManger::createRect(const std::vector<std::string>& param)
{
	GSvector2 pos(stof(param[5]), stof(param[6]));
	GSvector2 size(stof(param[7]), stof(param[8]));
	return MyRectangle(pos, size);
}

Star* StarManger::createStar(const std::vector<std::string>& param)
{
	GSvector2 pos(stof(param[1]), stof(param[2]));
	GSvector2 viewSize(stof(param[3]), stof(param[4]));
	MyRectangle rect = createRect(param);

	/*
	*���̐����ʒu�Ƃ̋����𑪂�
	*helf�ȏ�ɂȂ����������悤�ɂȂ��Ă���
	*
	*���̃s�b�N�A�b�v������
	*�@�����ʒu�ƃv���C���[�̋�����helf���ׂ���ǂ�����!?
	*/
	float maxhelth = stof(param[9]);

	StarMove_Ptr move = StarMove_Ptr(createMove(param,10));
	//nonmove
	int lastParamIndex = 11 + move->length();

	switch (stoi(param[0]))
	{
	case DEF:
		return new Star("star.bmp", pos, viewSize, rect, maxhelth, move,&effectMediator);
	case BREAK:		
		return new BreakStar("starb.bmp", pos, viewSize, rect, maxhelth, move, stof(param[lastParamIndex]), &effectMediator);
	case BRUN:
		return new BurnStar("starbrun.bmp", pos, viewSize, rect, maxhelth, move, &effectMediator);
	}
	return NULL;
}

void StarManger::createData()
{
	StarDataStream stream;
	std::vector<std::vector<std::string>>data;
	data.clear();
	stream.input(&data, "stardata\\stage0.stardata");
	/*
	* STARCLASS, posx,poy,veiwsizex,veiwsizey,rectsizew,rectsizeh,
	*  def: Imove
	*  break: Imove,dura
	*  brun: Imove,
	*/
	for each (std::vector<std::string> param in data)
	{
		factory.emplace_back(Fact_Ptr(new StarFactory(createStar(param), 3.0f, mediator)));
		//stars.emplace_back(Star_Ptr(createStar(param)));
	}
}
//�X�^�[����
//�t�@�C����ǂݍ���Ō^�𐶐�
void StarManger::createStarProt()
{
	createData();
}

//���^�R���e�i�̒��ŉ�ʓ��ɓ����Ă��鐯���s�b�N�A�b�v���Ċi�[
void StarManger::addInScreenStars()
{
	for each (Star_Ptr star in stars)
	{
		//if (scroll.isInsideWindow(star->getSPosi(), GSvector2(64,64)))
		inScreens.emplace_back(star->clone());
		mediator.add(inScreens.back());
	}
}

void StarManger::updata()
{
	//starResporn();
	remove();
	for each(Fact_Ptr sf in factory)
	{
		sf->update();
	}
}

void StarManger::findDeads(std::vector<Star_Ptr>* deads)
{
	for each (Star_Ptr s in inScreens)
	{
		if (s->getIsDead())
		{
			deads->emplace_back(s);
		}
	}
}

//����ł��𕜊�������
void StarManger::starResporn()
{
	//find_if���ƍŏ��Ɍ��������̂�Ԃ�
	//�ŏ��Ɍ��������̂������X�|�[��

	//�Ō�Ɍ��������̂�Ԃ��֐��������Ď�������
	//�ŏ��ɕԂ�������(�Ō�Ɍ���������)�������X�|�[��

	//gameObjectControl�Ő������폜���Ȃ��悤�ɂ������Ǖω��Ȃ�
	//inScreen�̍폜�����������Ə�L�̏����Ń��X�|�[�����ʎY�����

	//�Ȃ̂�isDead��true�̐���vector�ɂ��ׂĒǉ���
	//�ǉ����ꂽ�S�Ă̐��̃N���[��������mediator�ɓo�^

	std::vector<Star_Ptr> deads;
	deads.clear();
	findDeads(&deads);
	if (deads.empty())
	{
		return;
	}
	for each (Star_Ptr star in deads)
	{
		inScreens.emplace_back(star->clone());
		mediator.add(inScreens.back());
	}
}
void StarManger::remove()
{
	auto itrNewEnd = std::remove_if(inScreens.begin(), inScreens.end(), [](Star_Ptr obj)->bool
	{
		return obj->getIsDead();
	});
	inScreens.erase(itrNewEnd, inScreens.end());
}
Stars_inScreen& StarManger::getInScreenStars()
{
	return inScreens;
}