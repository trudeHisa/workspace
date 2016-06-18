#include "Operation.h"

#include "Device.h"
Operation::Operation(Device& device)
	:device(device), isEnd(false),
	fadeIn(), fadeOut()
{
}

Operation::~Operation()
{
}
void Operation::Init()
{
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();
	isEnd = false;
}
void Operation::Update()
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
	}
	isEnd = fadeOut.getIsEnd();
}
void Operation::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("operation.bmp", &GSvector2(0, 0));
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void Operation::Finish()
{

}
Scene Operation::Next()
{
	return MODE_MENU;
}
bool Operation::IsEnd()
{
	return isEnd;
}