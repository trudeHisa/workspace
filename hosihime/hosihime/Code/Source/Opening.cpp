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
	textPos_D = GSvector2(0, 720);//�e�L�X�g�̏����ʒu
	textPos = textPos_D;
	vel = GSvector2(0, 0);
	isEnd = false;
}

void Opening::Update()
{
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
	return MODE_TITLE;
}

bool Opening::IsEnd()
{
	return isEnd;
}