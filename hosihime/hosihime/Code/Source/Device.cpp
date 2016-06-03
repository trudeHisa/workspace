#include "Device.h"

Device::Device()
{
}
Renderer& Device::getNonConstRenderer()
{
	return renderer;
}
Sound& Device::getNonConstSound()
{
	return sound;
}
//const ’Êí‚±‚¿‚ç‚ğg‚¤
const Renderer& Device::getRenderer()const
{
	return renderer;
}
const Sound& Device::getSound()const
{
	return sound;
}
const Input& Device::getInput()const
{
	return input;
}
const CSVStream& Device::getCsvStream()const
{
	return csvStream;
}
const StarDataStream& Device::getStarDataStream()const
{
	return starDataStream;
}
void Device::release()
{
	renderer.Release();
	sound.Release();
}