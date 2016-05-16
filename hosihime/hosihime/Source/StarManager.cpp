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
//スター生成
//ファイルを読み込んで型を生成
void StarManger::createStarProt()
{
	stars.push_back(new Star("star.bmp", GSvector2(100, 100), mediator));
	stars.push_back(new Star("star.bmp", GSvector2(100, 200), mediator));
}

//原型コンテナの中で画面内に入っている星をピックアップして格納
void StarManger::addInScreenStars()
{
	inScreens.push_back(stars[0]->clone());
}
//死んでるやつを復活させる
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