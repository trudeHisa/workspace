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
	renderer.DrawTextrue("stageClear.bmp", &GSvector2(100, 100));
	renderer.DrawString("クリアタイム：：", &GSvector2(100, 400), 50);
	int num = static_cast<int>(score.getScore() / FRAMETIME);
	renderer.DrawNumber("number.bmp", GSvector2(400, 390), 80, 70,num);
	renderer.DrawString("秒", &GSvector2(470, 420), 30);
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