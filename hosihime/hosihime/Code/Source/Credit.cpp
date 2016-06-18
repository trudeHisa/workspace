#include "Credit.h"

#include "Device.h"
Credit::Credit(Device& device)
	:device(device), isEnd(false)
{
}

Credit::~Credit()
{
}
void Credit::Init()
{
	isEnd = false;
}
void Credit::Update()
{

}
void Credit::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("staffroll.bmp", &GSvector2(0, 0));
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