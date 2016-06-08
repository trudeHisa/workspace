#include "StarManager.h"
#include <algorithm>

#include "StarMediator.h"

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
StarManger::StarManger(Scroll& _scroll)
	:scroll(_scroll)
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
IStarMove* StarManger::createMove(const std::vector<std::string>& param)
{
	int type = stoi(param[9]);
	switch (type)
	{
	case CRICLE:
		return new Star_circle(stof(param[10]));
	case EIGHT:
		return new Star_eight(stof(param[10]), stof(param[11]));
	case PARABOLA:
		return new Star_paradola(stof(param[10]));
	case PENDULAM:
		return new Star_pendulum(stof(param[10]), stof(param[11]));
	case SLASHDOWN:
		return new Star_slashdown(GSvector2(stof(param[10]), stof(param[11])));
	case WAVE:
		return new Star_wave(GSvector2(stof(param[10]), stof(param[11])), stof(param[12]));
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

	StarMove_Ptr move = StarMove_Ptr(createMove(param));
	int lastParamIndex = 9 + move->length();
	int type = stoi(param[0]);
	switch (type)
	{
	case DEF:
		return new Star("star.bmp", pos, viewSize, rect, move);
	case BREAK:		
		return new BreakStar("starb.bmp", pos, viewSize, rect, move,stof(param[lastParamIndex]));
	case BRUN:
		return new BurnStar("star.bmp", pos, viewSize, rect, move);
	}
	return NULL;
}

void StarManger::createData()
{
	StarDataStream stream;
	std::vector<std::vector<std::string>>data;
	data.clear();
	stream.input(&data, "stardata\\stage.stardata");
	/*
	* STARCLASS, posx,poy,veiwsizex,veiwsizey,rectsizew,rectsizeh,
	*  def: Imove
	*  break: Imove,dura
	*  brun: Imove,
	*/
	for each (std::vector<std::string> param in data)
	{
		stars.emplace_back(Star_Ptr(createStar(param)));
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
	for each (Star_Ptr star in stars)
	{
		//if (scroll.isInsideWindow(star->getSPosi(), GSvector2(64,64)))
		inScreens.emplace_back(star->clone());
	}
}

void StarManger::updata()
{
	starResporn();
	remove();
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
		mediator->reqestClone(inScreens.back());
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