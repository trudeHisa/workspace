#include "StarManager.h"
#include <algorithm>
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
//スター生成
//ファイルを読み込んで型を生成
void StarManger::createStarProt()
{
	stars.push_back(new Star("star.bmp", GSvector2(100, 100)));
	stars.push_back(new Star("star.bmp", GSvector2(100, 200)));
}

//原型コンテナの中で画面内に入っている星をピックアップして格納
void StarManger::addInScreenStars()
{
	inScreens.push_back(stars[0]->clone());
	inScreens.push_back(stars[1]->clone());

}
//死んでるやつを復活させる
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