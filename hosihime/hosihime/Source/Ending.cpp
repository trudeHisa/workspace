#include "Ending.h"
#include "Input.h"
Ending::Ending(const Input& input)
	:input(input)
{
}
Ending::~Ending()
{
}
void Ending::Init()
{
	isEnd = false;
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