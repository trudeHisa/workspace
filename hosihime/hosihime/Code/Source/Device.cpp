#include "Device.h"

Device::Device()
{
}
//Renderer& Device::getNonConstRenderer()
//{
//	return renderer;
//}
Sound& Device::getNonConstSound()
{
	return sound;
}
//const 通常こちらを使う
//const Renderer& Device::getRenderer()const
//{
//	return renderer;
//}
const Sound& Device::getSound()const
{
	return sound;
}
const Input& Device::getInput()const
{
	return input;
}
void Device::release()
{
	//renderer.Release();
	sound.Release();
}