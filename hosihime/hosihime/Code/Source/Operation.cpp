#include "Operation.h"

#include "Device.h"
Operation::Operation(Device& device)
	:device(device), isEnd(false)
{
}

Operation::~Operation()
{
}
void Operation::Init()
{
	isEnd = false;
}
void Operation::Update()
{
	isEnd = device.getInput().getActionTrigger();
}
void Operation::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("operation.bmp",&GSvector2(0,0));
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