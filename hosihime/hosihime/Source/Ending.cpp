#include "Ending.h"
Ending::Ending()
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
	isEnd = !!gsGetKeyTrigger(GKEY_SPACE);
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