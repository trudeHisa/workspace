#ifndef _DEVICE_H_
#define _DEVICE_H_

//#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
//Device�Ǘ�
class Device
{
public:
	Device();
	//load�p
	Sound& getNonConstSound();
	//const �ʏ킱������g��
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