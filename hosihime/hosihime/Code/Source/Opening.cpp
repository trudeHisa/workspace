#include "Opening.h"
#include "Device.h"

Opening::Opening(Device& device)
	:device(device), isend(false)
{
	
}

Opening::~Opening()
{

}

void Opening::init()
{
	textPos_D = GSvector2(0, 720);//テキストの初期位置
	textPos = textPos_D;
	vel = GSvector2(0, 0);
	isend = false;
}

void Opening::update()
{
	if (!device.getSound().isPlaySE("Opening.wav"))
	{
		device.getSound().playSE("Opening.wav");
	}
	isend = device.getInput().getActionTrigger();
	vel = GSvector2(0.0f, -2.0f);

	textPos += vel*gsFrameTimerGetTime();
	if (textPos.y <= -textPos_D.y)
	{
		isend = true;
	}
}

void Opening::draw(const Renderer& renderer)
{
	renderer.drawTextrue("opening.bmp", &GSvector2(0, 0));
	renderer.drawTextrue("opening_text.bmp", &textPos);
}

void Opening::finish()
{

}

Scene Opening::next()
{
	device.getSound().stopSE("Opening.wav");
	return Scene::MODE_TITLE;
}

bool Opening::isEnd()
{
	return isend;
}