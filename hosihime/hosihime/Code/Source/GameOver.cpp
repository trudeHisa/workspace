#include "../Include/GameOver.h"
#include "../Include/Device.h"
GameOver::GameOver(Device& device)
:device(device), isEnd(false)
{

}
GameOver::~GameOver()
{

}
void GameOver::Init()
{
	isEnd = false;
}
void GameOver::Update()
{
	if (device.getInput().getActionTrigger())
	{
		isEnd = true;
	}
}
void GameOver::Draw(const Renderer& renderer)
{
	renderer.DrawString("ゲームオーバー",&GSvector2(100, 100), 50);
}
void GameOver::Finish()
{}
Scene GameOver::Next()
{
	return MODE_TITLE;
}
bool GameOver::IsEnd()
{
	return isEnd;
}
