#include "StarManager.h"
#include <algorithm>
#include "Star.h"
#include "StarMediator.h"

#include "Star_cricle.h"
#include "Star_eight.h"
#include "Star_parabola.h"
#include "Star_pendulum.h"
#include "Star_slashdown.h"
#include "Star_wave.h"
#include "Star_nomove.h"

#include "StarDataStream.h"

#include "STARTYPE.h"
StarManger::StarManger(Scroll& _scroll)
:scroll(_scroll)
{
}
StarManger::~StarManger()
{
	for each (Star* star in stars)
	{
		delete star;
	}
	//stars
}
void StarManger::initialize(StarMediator* _mediator)
{
	stars.clear();
	mediator = _mediator;
}
IStarMove* StarManger::createMove(std::vector<std::string>& param)
{
	switch (stoi(param[6]))
	{
	case CRICLE:
		return new Star_circle(stof(param[7]));
		break;
	case EIGHT:
		return new Star_eight(stof(param[7]), stof(param[8]));
		break;
	case PARABOLA:
		return new Star_paradola(stof(param[7]));
		break;
	case PENDULAM:
		return new Star_pendulum(stof(param[7]), stof(param[8]));
		break;
	case SLASHDOWN:
		return new Star_slashdown(GSvector2(stof(param[7]), stof(param[8])));
		break;
	case WAVE:
		return new Star_wave(GSvector2(stof(param[7]), stof(param[8])), stof(param[9]));
		break;
	case NOMOVE:
		return new Star_nomove();
		break;
	default:
		return NULL;
		break;
	}
}
MyRectangle StarManger::createRect(std::vector<std::string>& param)
{
	GSvector2 pos(stof(param[2]), stof(param[3]));
	GSvector2 size(stof(param[4]),stof(param[5]));
	return MyRectangle(pos,size);
}
void StarManger::createData()
{
	StarDataStream stream;
	std::vector<std::vector<std::string>>data;
	data.clear();
	stream.input(&data, "stardata\\stage.stardata");

	for each (std::vector<std::string> param in data)
	{
		switch (stoi(param[0]))
		{
		case DEF:
			stars.emplace_back(new Star(param[1],createRect(param),createMove(param)));
			break;
		case HIBI:

			break;
		}
	}
}
//スター生成
//ファイルを読み込んで型を生成
void StarManger::createStarProt()
{
	createData();
}

//原型コンテナの中で画面内に入っている星をピックアップして格納
void StarManger::addInScreenStars()
{
	for each (Star* star in stars)
	{
		//if (scroll.isInsideWindow(star->getSPosi(), GSvector2(64,64)))
		inScreens.push_back(star->clone());
	}
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