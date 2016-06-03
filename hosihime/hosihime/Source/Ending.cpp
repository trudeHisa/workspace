#include "Ending.h"
#include "Input.h"
Ending::Ending(Sound& sound,const Input& input)
	:sound(sound),input(input)
{
}
Ending::~Ending()
{
}
void Ending::Init()
{
	sound.StopSE("GameMode_1.wav");
	isEnd = false;
	sound.PlaySE("Ending.wav");
}
void Ending::Update()
{
	isEnd = input.getActionTrigger();
}
void Ending::Draw(Renderer& renderer)
{	
	renderer.DrawTextrue("ending.bmp", &GSvector2(0, 0));
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