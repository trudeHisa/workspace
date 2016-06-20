#include "Ending.h"
#include "Device.h"

Ending::Ending(Device& device, TimeScore& score)
: device(device), score(score), fadeIn(), fadeOut(),
anim(animTimer), animTimer(20.f)
{
}
Ending::~Ending()
{
}
void Ending::Init()
{
	fadeIn.initialize();
	fadeOut.initialize();
	isEnd = false;
	device.getSound().PlaySE("ending.wav");
	playerPosi = GSvector2(1280, 200);
	logoPosi = playerPosi + GSvector2(190, 50);
	vel = GSvector2(0, 0);
	anim.addCell("A", 1, 3, 208, 204);
	animTimer.initialize();
	animTimer.setStarTimer(30.f);

	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);
}
void Ending::Update()
{

	fadeIn.updata();
	if (!fadeIn.getIsEnd())return;

	vel = GSvector2(-2.0f, 0);
	playerPosi += vel;
	if (playerPosi.x > 0)
	{
		logoPosi = playerPosi;
	}
	anim.updata("A");
	animTimer.updata();
	fadeOut.updata();
	isEnd = fadeOut.getIsEnd();


	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void Ending::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("space0.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("con_logo.bmp", &logoPosi,&GSvector2(2,2),&GScolor(1,1,1,1));
	anim.draw(renderer, "kasasagi_end.bmp", &playerPosi);

	if (playerPosi.x < 0)
	{
		renderer.DrawString("スペースてを押してね",&GSvector2(300,600),30);
	}
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}


void Ending::Finish()
{
	device.getSound().StopSE("ending.wav");
}
Scene Ending::Next()
{
	return MODE_RESULT;
}
bool Ending::IsEnd()
{
	return isEnd;
}