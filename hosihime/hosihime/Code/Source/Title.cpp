#include "Title.h"

#include "Calculate.h"
#include "Device.h"
#include "Star_slashdown.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device, Background_Star& bStar)
	:device(device), rogoAlpha(0),
	timer(1, 1), bStar(bStar)
{}
Title::~Title()
{
}
void Title::Init()
{
	bStar.initialize();
	rogoAlpha = 0;
	
	timer.initialize();
	alpha = 255;
	isEnd = false;	
}
void Title::Update()
{
	bStar.update();

	rogoAlpha += gsFrameTimerGetTime()*0.02f;
	if (rogoAlpha >= 1)
	{
		if (!device.getSound().IsPlaySE("title.wav"))
		{
			device.getSound().PlaySE("title.wav");
		}		
		rogoAlpha = 1;
		if (device.getInput().getActionTrigger())
		{
			device.getSound().PlaySE("decision.wav");
			isEnd = true;
		}
	}

	timer.update();
	if (timer.isEnd())
	{
		timer.initialize();
		alpha = alpha == 255 ? 0 : 255;
	}
}
void Title::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));	
	bStar.draw(renderer);
	renderer.DrawTextrue("title_text.bmp", &GSvector2(200, 120), &GScolor(1, 1, 1, rogoAlpha));
	renderer.DrawTextrue("space_text.bmp", &GSvector2(480, 540), &GScolor(255, 255, 255, alpha));
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