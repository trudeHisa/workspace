#ifndef _DEVICE_H_
#define _DEVICE_H_

//#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
//DeviceŠÇ—
class Device
{
public:
	Device();
	//load—p
	Sound& getNonConstSound();
	//const ’Êí‚±‚¿‚ç‚ğg‚¤
	//const Renderer& getRenderer()const;
	const Sound& getSound()const;
	const Input& getInput()const;
	void release();
private:
	//Renderer renderer;
	Sound sound;
	Input input;
};
#endif