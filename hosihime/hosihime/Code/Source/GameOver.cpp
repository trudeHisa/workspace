#include "../Include/GameOver.h"
#include "../Include/Device.h"
#include"../Include/GamePlay.h"

#define  MOVETIME 60.f*2.f
#define DRAW_LOGO_TIME 60.f*4.f
#define LARGE GSvector2(1.2f, 1.2f)
#define SMALL GSvector2(0.8f, 0.8f)
#define ACTIVE_COLOR GSvector4(1, 0, 0, 1)
#define NON_ACTIVE_COLOR GSvector4(1, 1, 1, 1)

GameOver::GameOver(Device& device, GamePlay* _play)
:device(device), isEnd(false), play(_play), textPosi(300, -100),
time(MOVETIME), currentTime(0), alpha(1.0f), isSelectMode(false),
nowSelect(0), fadeIn(), fadeOut()
{
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
	currentTime = 0;
	time = MOVETIME;
	isEnd = false;
	alpha = 1.0f;
	textPosi=GSvector2(300, -100);
	isSelectMode = false;
}
void GameOver::Update()
{
	if (fadeIn.getIsEnd() == false) 	{
		fadeIn.updata();
		return;
	}
	currentTime += gsFrameTimerGetTime();
	if (textPosi.y < 100){
		gsVector2Lerp(&textPosi, &GSvector2(300, -200), &GSvector2(300, 100), currentTime / time);
	}
	if (currentTime >= DRAW_LOGO_TIME){
		alpha -= gsFrameTimerGetTime()*0.02f;
	}
	isSelectMode = alpha <= 0 ? true : false;
	if (device.getInput().getActionTrigger())
	{
		alpha = 0;
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
	if (isSelectMode == false)return;
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
	selectDraw(renderer);

	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}

void GameOver::selectDraw(const Renderer& renderer)
{
	if (isSelectMode == false)return;

	if (nowSelect == 0)
	{
		scales[0] = LARGE;
		colors[0] = ACTIVE_COLOR;
		scales[1] = SMALL;
		colors[1] = NON_ACTIVE_COLOR;
	}
	if (nowSelect == 1){
		scales[0] = SMALL;
		colors[0] = NON_ACTIVE_COLOR;
		scales[1] = LARGE;
		colors[1] = ACTIVE_COLOR;
	}
	renderer.DrawTextrue("retry.bmp", &GSvector2(50, 150), &scales[0], &colors[0]);
	renderer.DrawTextrue("titlebuck.bmp", &GSvector2(700, 150), &scales[1], &colors[1]);
}
void GameOver::Finish()
{
	device.getSound().StopSE("gameover.wav");
}
Scene GameOver::Next()
{
	if (nowSelect == 0)
	{
		play->Continue();
		return MODE_GAMEPLAY;
	}

	return MODE_TITLE;
}
bool GameOver::IsEnd()
{
	return isEnd;
}
