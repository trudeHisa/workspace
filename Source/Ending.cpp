#include "Ending.h"
#include "Input.h"
Ending::Ending(const Input& input, TimeScore& score)
:input(input), score(score)
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