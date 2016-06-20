#include "../Include/GameOver.h"
#include "../Include/Device.h"
GameOver::GameOver(Device& device)
:device(device), isEnd(false), textPosi(100, -200),
time(60.f * 2), currentTime(0), alpha(1.0f), isSelectMode(false),
nowSelect(0), fadeIn(), fadeOut()
{
	iconPosi[0] = GSvector2(360, 200);
	iconPosi[1] = GSvector2(760, 200);
}
GameOver::~GameOver()
{

}
void GameOver::Init()
{
	device.getSound().PlaySE("gameover.wav");
	nowSelect = 0;
	fadeIn.initialize();
	fadeOut.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 2.0f);
	isEnd = false;
}
void GameOver::Update()
{
	if (fadeIn.getIsEnd() == false) 	{
		fadeIn.updata();
		return;
	}
	currentTime += gsFrameTimerGetTime();
	if (textPosi.y < 100){
		gsVector2Lerp(&textPosi, &GSvector2(100, -200), &GSvector2(100, 100), currentTime / time);
	}
	if(currentTime>=60.f*3.5f){
		alpha -= gsFrameTimerGetTime()*0.02f;
		isSelectMode = alpha < 0 ? true : false;
	}

	if (isSelectMode)
	{
		if (device.getInput().getRightTrigger() || device.getInput().getLeftTrigger())
		{
			device.getSound().PlaySE("move.wav");
			nowSelect = nowSelect == 0 ? 1 : 0;
		}
	}


	FadeOut();
}

void GameOver::FadeOut()
{
	fadeOut.updata();
	isEnd = fadeOut.getIsEnd();
	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		device.getSound().PlaySE("decision.wav");
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void GameOver::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("gameover.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("gameover_text.bmp", &textPosi, &GScolor(1, 1, 1, alpha));
	renderer.DrawTextrue("gameover_orihime.bmp", &GSvector2(350, 300));

	if (isSelectMode)
	{
		renderer.DrawString("‚à‚¤‚¢‚Á‚©‚¢I", &GSvector2(400, 200), 30);
		renderer.DrawString("‚ ‚«‚ç‚ß‚é...", &GSvector2(800, 200), 30);
		renderer.DrawTextrue("Icon.bmp", &iconPosi[nowSelect]);
	}

	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void GameOver::Finish()
{
	device.getSound().StopSE("gameover.wav");
}
Scene GameOver::Next()
{
	if (nowSelect==0)
	{
		return MODE_GAMEPLAY;
	}

	return MODE_TITLE;
}
bool GameOver::IsEnd()
{
	return isEnd;
}
