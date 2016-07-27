#include "Title.h"

#include "Calculate.h"
#include "Device.h"
#include "Star_slashdown.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device, Background_Star& bStar)
	:device(device), rogoAlpha(0),
	timer(1, 1), bStar(bStar), isend(false)
{}
Title::~Title()
{
}
void Title::init()
{
	bStar.initialize();
	rogoAlpha = 0;
	
	timer.initialize();
	alpha = 255;
	isend = false;	
}
void Title::update()
{
	bStar.update();
	rogoAlpha += gsFrameTimerGetTime()*0.02f;
	if (rogoAlpha >= 1)
	{
		if (!device.getSound().isPlaySE("title.wav"))
		{
			device.getSound().playSE("title.wav");
		}		
		rogoAlpha = 1;
		if (device.getInput().getActionTrigger() || gsGetJoyTrigger(0,GJOY_BUTTON_8))
		{
			device.getSound().playSE("decision.wav");
			isend = true;
		}
	}

	timer.update();
	if (timer.isEnd())
	{
		timer.initialize();
		alpha = alpha == 255 ? 0 : 255;
	}
}
void Title::draw(const Renderer& renderer)
{
	renderer.drawTextrue("title.bmp", &GSvector2(0, 0));	
	bStar.draw(renderer);
	renderer.drawTextrue("title_text.bmp", &GSvector2(180, 120), &GScolor(1, 1, 1, rogoAlpha));
	renderer.drawTextrue("space_text.bmp", &GSvector2(320, 540), &GScolor(255, 255, 255, alpha));
}
void Title::finish()
{
}
Scene Title::next()
{
	return Scene::MODE_MENU;
}
bool Title::isEnd()
{
	return isend;
}