#include "StarManager.h"
#include <algorithm>
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
	stars.push_back(new Star("star.bmp", GSvector2(100, 100), new Star_wave(GSvector2(1, 3), 5)));
	stars.push_back(new Star("star.bmp", GSvector2(100, 200), new Star_wave(GSvector2(1, 3), 5)));
}
//���^�R���e�i�̒��ŉ�ʓ��ɓ����Ă��鐯���s�b�N�A�b�v���Ċi�[
void StarManger::addInScreenStars()
{
	inScreens.push_back(stars[0]->clone());
	inScreens.push_back(stars[1]->clone());

}
//����ł��𕜊�������
void StarManger::StarResporn()
{
		auto itr = std::find_if(inScreens.begin(), inScreens.end(), [](Star* obj)
		{
			return obj->getIsDead();
		});
		if (itr == inScreens.end())
		{
			return;
		}

		inScreens.push_back((*itr)->clone());
		mediator->reqestClone(inScreens.back());

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