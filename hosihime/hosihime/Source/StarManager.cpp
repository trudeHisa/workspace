#include "StarManager.h"
#include <algorithm>
#include "Star.h"
#include "StarMediator.h"

#include "Star_cricle.h"
#include "Star_pendulum.h"
#include "Star_wave.h"
#include "Star_eight.h"

StarManger::StarManger() {
}
StarManger::~StarManger()
{
}
void StarManger::initialize(StarMediator* _mediator)
{
	stars.clear();
	mediator = _mediator;
}
//�X�^�[����
//�t�@�C����ǂݍ���Ō^�𐶐�
void StarManger::createStarProt()
{
	stars.push_back(new Star("star.bmp", GSvector2(200, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(100, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(300, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(400, 100), new Star_wave(GSvector2(1, 3), 3)));
}

//���^�R���e�i�̒��ŉ�ʓ��ɓ����Ă��鐯���s�b�N�A�b�v���Ċi�[
void StarManger::addInScreenStars()
{
	inScreens.push_back(stars[0]->clone());
	inScreens.push_back(stars[1]->clone());
	inScreens.push_back(stars[3]->clone());
	inScreens.push_back(stars[2]->clone());
}

void StarManger::updata()
{
	starResporn();
	remove();
}

void StarManger::findDeads(std::vector<Star*>* deads)
{
	for each (Star* s in inScreens)
	{
		if (s->getIsDead())
		{
			deads->push_back(s);
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

	std::vector<Star*> deads;
	deads.clear();
	findDeads(&deads);
	if (deads.empty())
	{
		return;
	}
	for each (Star* star in deads)
	{
		inScreens.push_back(star->clone());
		mediator->reqestClone(inScreens.back());
	}
}
void StarManger::remove()
{
	auto itrNewEnd = std::remove_if(inScreens.begin(), inScreens.end(), [](Star* obj)->bool
	{
		return obj->getIsDead();
	});
	inScreens.erase(itrNewEnd, inScreens.end());
}
Stars_inScreen& StarManger::getInScreenStars()
{
	return inScreens;
}