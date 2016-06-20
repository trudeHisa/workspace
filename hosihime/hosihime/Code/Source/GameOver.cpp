#include "../Include/GameOver.h"
#include "../Include/Device.h"
GameOver::GameOver(Device& device)
:device(device), isEnd(false),textPosi(50,-50), 
time(60.f * 2), currentTime(0), alpha(1.0f),
fadeIn(), fadeOut()
{

}
GameOver::~GameOver()
{

}
void GameOver::Init()
{
	device.getSound().PlaySE("gameover.wav");
	fadeIn.initialize();
	fadeOut.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0),2.0f);
	isEnd = false;
}
void GameOver::Update()
{
	if (fadeIn.getIsEnd() == false) 	{
		fadeIn.updata();
		return;
	}
	currentTime += gsFrameTimerGetTime();
	if (textPosi.y <100){
		gsVector2Lerp(&textPosi, &GSvector2(50, -50), &GSvector2(50, 100), currentTime / time);
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
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void GameOver::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("gameover.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("gameover_text.bmp", &textPosi);
	renderer.DrawTextrue("gameover_orihime.bmp", &GSvector2(350, 400));

	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void GameOver::Finish()
{
	device.getSound().StopSE("gameover.wav");
}
Scene GameOver::Next()
{
	return MODE_TITLE;
}
bool GameOver::IsEnd()
{
	return isEnd;
}
