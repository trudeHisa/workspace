#include "Ending.h"
#include "Device.h"

Ending::Ending(Device& device, TimeScore& score)
: device(device), score(score), fadeIn(), fadeOut()
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
	playerPosi = GSvector2(1280, 300);
	vel = GSvector2(0, 0);

	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);
}
void Ending::Update()
{
	vel = GSvector2(-2.0f, 0);
	playerPosi += vel;
	fadeIn.updata();
	fadeOut.updata();
	isEnd = fadeOut.getIsEnd();


	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1),1.0f);
	}
}
void Ending::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("space0.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("orihime.bmp",&playerPosi);
	renderer.DrawString("エンディング", &GSvector2(50, 50), 50);

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