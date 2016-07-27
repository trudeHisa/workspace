#include "Operation.h"

#include "Device.h"
Operation::Operation(Device& device)
	:device(device), isend(false),
	fadeIn(), fadeOut(), index(0)
{
}

Operation::~Operation()
{
}
void Operation::init()
{
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();
	isend = false;
	index = 0;
}
void Operation::update()
{
	if (gsGetKeyTrigger(GKEY_SPACE)||gsGetJoyTrigger(0,GJOY_BUTTON_1))
	{
		index += 1;
	}
	fadeIn.updata();
	fadeOut.updata();
	/*if (!fadeIn.getisEnd())
	{
		return;
	}
	if (!fadeOut.getIsStart())
	{
		if (!device.getInput().getActionTrigger())
		{
			return;
		}
		device.getSound().playSE("decision.wav");
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}*/
	isend = fadeOut.getisEnd();
}
void Operation::draw(const Renderer& renderer)
{	
	const std::string Tex[3] =
	{
		"Control",
		"stage_commentary",
		"object"
	};
	if (index == 3)
	{
		index -= 1;
		isend = true;
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
	renderer.drawTextrue(Tex[index] + ".bmp", &GSvector2(0, 0));
	
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void Operation::finish()
{

}
Scene Operation::next()
{
	return Scene::MODE_MENU;
	
}
bool Operation::isEnd()
{
	return isend;
}
void  Operation::Texchange()
{
	
}