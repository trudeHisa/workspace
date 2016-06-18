#include "Credit.h"

#include "Device.h"
Credit::Credit(Device& device)
	:device(device), isEnd(false),
	fadeIn(), fadeOut()
{
}

Credit::~Credit()
{
}
void Credit::Init()
{
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();
	isEnd = false;
}
void Credit::Update()
{
	fadeIn.updata();
	fadeOut.updata();
	if (!fadeIn.getIsEnd())
	{
		return;
	}
	if (!fadeOut.getIsStart())
	{
		if (!device.getInput().getActionTrigger())
		{
			return;
		}
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
		device.getSound().PlaySE("decision.wav");
	}
	isEnd = fadeOut.getIsEnd();
}
void Credit::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("staffroll.bmp", &GSvector2(0, 0));
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void Credit::Finish()
{

}
Scene Credit::Next()
{
	return MODE_MENU;
}
bool Credit::IsEnd()
{
	return isEnd;
}