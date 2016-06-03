#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
#include "CSVStream.h"
#include "StarDataStream.h"
//Device�Ǘ�
class Device
{
public:
	Device();
	//load�p
	Renderer& getNonConstRenderer();
	Sound& getNonConstSound();
	//const �ʏ킱������g��
	const Renderer& getRenderer()const;
	const Sound& getSound()const;
	const Input& getInput()const;
	const CSVStream& getCsvStream()const;
	const StarDataStream& getStarDataStream()const;

	void release();
private:
	Renderer renderer;
	Sound sound;
	Input input;
	CSVStream csvStream;
	StarDataStream starDataStream;
};
#endif