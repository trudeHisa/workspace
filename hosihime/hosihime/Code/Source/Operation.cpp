#include "Operation.h"

#include "Device.h"
Operation::Operation(Device& device)
	:device(device), isEnd(false),
	fadeIn(), fadeOut(), index(0)
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
	index = 0;
}
void Operation::Update()
{
	if (gsGetKeyTrigger(GKEY_SPACE)||gsGetJoyTrigger(0,GJOY_BUTTON_1))
	{
		index += 1;
	}
	fadeIn.updata();
	fadeOut.updata();
	/*if (!fadeIn.getIsEnd())
	{
		return;
	}
	if (!fadeOut.getIsStart())
	{
		if (!device.getInput().getActionTrigger())
		{
			return;
		}
		device.getSound().PlaySE("decision.wav");
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}*/
	isEnd = fadeOut.getIsEnd();
}
void Operation::Draw(const Renderer& renderer)
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
		isEnd = true;
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
	renderer.DrawTextrue(Tex[index] + ".bmp", &GSvector2(0, 0));
	
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void Operation::Finish()
{

}
Scene Operation::Next()
{
	return Scene::MODE_MENU;
	
}
bool Operation::IsEnd()
{
	return isEnd;
}
void  Operation::TexChange()
{
	
}