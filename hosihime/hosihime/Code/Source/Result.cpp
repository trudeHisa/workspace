#include "Result.h"
#include "Device.h"
Result::Result(Device& device, TimeScore& score)
:device(device), score(score)
{
}
Result::~Result()
{
}
void Result::Init()
{
	isEnd = false;
	device.getSound().PlaySE("ending.wav");
}
void Result::Update()
{
	isEnd = device.getInput().getActionTrigger();
}
void Result::Draw(const Renderer& renderer)
{
	renderer.DrawString("ƒŠƒUƒ‹ƒg", &GSvector2(50, 50), 50);
	renderer.DrawString(std::to_string((int)(score.getScore() / FRAMETIME)), &GSvector2(50, 50), 50);
}
void Result::Finish()
{
}
Scene Result::Next()
{
	return MODE_GAMEPLAY;
}
bool Result::IsEnd()
{
	return isEnd;
}