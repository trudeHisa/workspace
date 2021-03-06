#ifndef _DEVICE_H_
#define _DEVICE_H_

//#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
//Device管理
class Device
{
public:
	Device();
	//load用
	Sound& getNonConstSound();
	//const 通常こちらを使う
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