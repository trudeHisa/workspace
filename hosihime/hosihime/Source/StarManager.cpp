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
//スター生成
//ファイルを読み込んで型を生成
void StarManger::createStarProt()
{
	stars.push_back(new Star("star.bmp", GSvector2(200, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(100, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(300, 100), new Star_wave(GSvector2(1, 3), 3)));
	stars.push_back(new Star("star.bmp", GSvector2(400, 100), new Star_wave(GSvector2(1, 3), 3)));
}

//原型コンテナの中で画面内に入っている星をピックアップして格納
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

//死んでるやつを復活させる
void StarManger::starResporn()
{
	//find_ifだと最初に見つけたものを返す
	//最初に見つけたものだけリスポーン

	//最後に見つけたものを返す関数をつくって試したら
	//最初に返したもの(最後に見つけたもの)だけリスポーン

	//gameObjectControlで星だけ削除しないようにしたけど変化なし
	//inScreenの削除処理を消すと上記の条件でリスポーンが量産される

	//なのでisDeadがtrueの星をvectorにすべて追加し
	//追加された全ての星のクローンをつくりmediatorに登録

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