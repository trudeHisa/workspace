#include "Ending.h"
#include "Device.h"

Ending::Ending(Device& device, TimeScore& score)
: device(device), score(score)
{
}
Ending::~Ending()
{
}
void Ending::Init()
{
	device.getSound().StopSE("GameMode_1.wav");
	isEnd = false;
	device.getSound().PlaySE("Ending.wav");
	playerPosi = GSvector2(1280, 300);
	vel = GSvector2(0, 0);
}
void Ending::Update()
{
	isEnd = device.getInput().getActionTrigger();
	vel = GSvector2(-2.0f, 0);

	playerPosi += vel;

}
void Ending::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("space0.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("player.bmp",&playerPosi);
	renderer.DrawString("エンディング", &GSvector2(50, 50), 50);
}

void Ending::Finish()
{
}
Scene Ending::Next()
{
	return MODE_RESULT;
}
bool Ending::IsEnd()
{
	return isEnd;
}