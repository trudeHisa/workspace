#include "Opening.h"
#include "Device.h"

Opening::Opening(Device& device)
	:device(device)
{
	
}

Opening::~Opening()
{

}

void Opening::Init()
{
	textPos_D = GSvector2(0, 720);//テキストの初期位置
	textPos = textPos_D;
	vel = GSvector2(0, 0);
	isEnd = false;
}

void Opening::Update()
{
	if (!device.getSound().IsPlaySE("Opening.wav"))
	{
		device.getSound().PlaySE("Opening.wav");
	}
	isEnd = device.getInput().getActionTrigger();
	vel = GSvector2(0.0f, -2.0f);

	textPos += vel;
	if (textPos.y <= -textPos_D.y)
	{
		isEnd = true;
	}
}

void Opening::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("opening.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("opening_text.bmp", &textPos);
}

void Opening::Finish()
{

}

Scene Opening::Next()
{
	device.getSound().StopSE("Opening.wav");
	return Scene::MODE_TITLE;
}

bool Opening::IsEnd()
{
	return isEnd;
}