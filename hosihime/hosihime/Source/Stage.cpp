#include "Stage.h"
#include "game.h"

#include "GameObjectFactory.h"
#include "Device.h"

#include<memory>
#include "CSVStream.h"

#define  BLOCKSIZE 64.f
Stage::Stage(const std::string& csvname, Device& device)
	:scroll(WINDOW_WIDTH, WINDOW_HEIGHT), timer(60,60)
	, starManager(scroll), device(device)
{
	CSVStream stream;
	stream.input(&mapdata, csvname.c_str());
}
Stage::~Stage()
{
}
void Stage::initialize()
{
	//device.getSound().PlaySE("GameMode_1.wav");
	timer.initialize();
	control.inisialize();
	starManager.initialize(&control);
	scroll.initialize();
	mapCreate();
	Stars_IsInScreen();
	isEnd = false;
}
void Stage::updata()
{
	starManager.updata();
	control.updata();
	timer.update();
	if (timer.isEnd() || control.isDeadPlayer())
	{		
		timer.stop();
		isEnd = true;
	}
}
void Stage::draw(const Renderer& renderer)
{
	scroll.draw(renderer);
	control.draw(renderer,scroll);
	int t = timer.getTime()/FRAMETIME;
	renderer.DrawString(std::to_string(t), &GSvector2(50, 50), 50);
}
void Stage::finish()
{
	control.finish();
}

void Stage::saveScore(TimeScore& score)
{
	score.setScore(timer);
}

bool Stage::getIsEnd()
{
	return isEnd;
}

void Stage::objCreate(int x, int y)
{
	int data = mapdata(y, x);
	if (0 == data)
	{
		return;
	}	
	GSvector2 pos = GSvector2(x * BLOCKSIZE, y* BLOCKSIZE);
	std::shared_ptr<Factory> factory = std::shared_ptr<Factory>(new GameObjectFactory(scroll, device));
	control.add(factory->create(static_cast<GAMEOBJ_TYPE>(data), pos));	
}
void Stage::mapCreate()
{
	for (int y = 0; y < mapdata.getSize0(); y++)
	{
		for (int x = 0; x < mapdata.getSize1(); x++)
		{
			objCreate(x, y);
		}
	}
	//�X�^�[�̌��^��S������
	starManager.createStarProt();
}

void Stage::Stars_IsInScreen()
{
	//��ʓ��ɓ����Ă鐯������
	starManager.addInScreenStars();
	//objcontrol�ɒǉ�
	control.add_Star(starManager.getInScreenStars());
}