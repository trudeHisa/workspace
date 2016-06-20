#include "Result.h"
#include "Device.h"
Result::Result(Device& device, TimeScore& score)
:device(device), score(score), fadeIn(), fadeOut()
{
}
Result::~Result()
{
}
void Result::Init()
{
	fadeIn.initialize();
	fadeOut.initialize();
	isEnd = false;
	device.getSound().PlaySE("ending.wav");
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);
}
void Result::Update()
{
	fadeIn.updata();
	if (fadeIn.getIsEnd() == false)return;

	fadeOut.updata();
	isEnd = fadeOut.getIsEnd();

	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0,0,0,0),GScolor(0,0,0,1),1.0f);
	}
}
void Result::Draw(const Renderer& renderer)
{
	renderer.DrawString("ƒŠƒUƒ‹ƒg", &GSvector2(50, 50), 50);
	renderer.DrawString(std::to_string((int)(score.getScore() / FRAMETIME)), &GSvector2(50, 50), 50);
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
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