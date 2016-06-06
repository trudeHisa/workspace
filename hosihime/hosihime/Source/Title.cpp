#include "Title.h"

#include "Calculate.h"
#include "Device.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device)
	:device(device)
{
}
Title::~Title()
{
}
void Title::Init()
{
//	device.getSound().StopSE("Ending.wav");
	//device.getSound().PlaySE("Opening.wav");
	isEnd = false;	
}
void Title::Update()
{
	isEnd =device.getInput().getActionTrigger();
}
void Title::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titletext.bmp", &GSvector2(200, 120));
	renderer.DrawTextrue("spacetext.bmp", &GSvector2(480, 540));
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