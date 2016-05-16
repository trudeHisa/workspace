#include "StarManager.h"

StarManger::StarManger()
{
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
	stars.push_back(new Star("star.bmp", GSvector2(100, 100), mediator));
	stars.push_back(new Star("star.bmp", GSvector2(100, 200), mediator));
}

//���^�R���e�i�̒��ŉ�ʓ��ɓ����Ă��鐯���s�b�N�A�b�v���Ċi�[
void StarManger::addInScreenStars()
{
	inScreens.push_back(stars[0]->clone());
}
//����ł��𕜊�������
void StarManger::StarResporn()
{
	for each (Star* n in inScreens)
	{
		if (n->getIsDead())
		{
			mediator->reqestClone(n->clone());
		}
	}
}

Stars_inScreen& StarManger::getInScreenStars()
{
	return inScreens;
}