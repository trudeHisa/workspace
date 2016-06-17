#include "Title.h"

#include "Calculate.h"
#include "Device.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device)
:device(device), timer(1,1)
{
}
Title::~Title()
{
}
void Title::Init()
{

//	device.getSound().StopSE("Ending.wav");
	//device.getSound().PlaySE("Opening.wav");
	timer.initialize();
	alpha = 255;
	isEnd = false;	
}
void Title::Update()
{
	timer.update();
	if (timer.isEnd())
	{
		timer.initialize();
		alpha = alpha == 255 ? 0 : 255;
	}
	isEnd =device.getInput().getActionTrigger();
}
void Title::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titletext.bmp", &GSvector2(200, 120));
	renderer.DrawTextrue("spacetext.bmp", &GSvector2(480, 540), &GScolor(255, 255, 255, alpha));

}
void Title::Finish()
{
}
Scene Title::Next()
{
	return MODE_MENU;
}
bool Title::IsEnd()
{
	return isEnd;
}