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
}
void Ending::Update()
{
	isEnd = device.getInput().getActionTrigger();
}
void Ending::Draw(const Renderer& renderer)
{	
	renderer.DrawTextrue("ending.bmp", &GSvector2(0, 0));
	renderer.DrawString(std::to_string(score.getScore()/FRAMETIME), &GSvector2(50, 50), 50);
}
void Ending::Finish()
{
}
Scene Ending::Next()
{
	return MODE_TITLE;
}
bool Ending::IsEnd()
{
	return isEnd;
}