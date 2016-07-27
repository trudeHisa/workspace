#include "Credit.h"

#include "Device.h"
Credit::Credit(Device& device)
	:device(device), isend(false),
	fadeIn(), fadeOut()
{
}

Credit::~Credit()
{
}
void Credit::init()
{
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();
	isend = false;
}
void Credit::update()
{
	fadeIn.updata();
	fadeOut.updata();
	if (!fadeIn.getisEnd())
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
		device.getSound().playSE("decision.wav");
	}
	isend = fadeOut.getisEnd();
}
void Credit::draw(const Renderer& renderer)
{
	renderer.drawTextrue("staffroll.bmp", &GSvector2(0, 0));
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void Credit::finish()
{

}
Scene Credit::next()
{
	return Scene::MODE_MENU;
}
bool Credit::isEnd()
{
	return isend;
}