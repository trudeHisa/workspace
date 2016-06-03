#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
#include "CSVStream.h"
#include "StarDataStream.h"
//Device管理
class Device
{
public:
	Device();
	//load用
	Renderer& getNonConstRenderer();
	Sound& getNonConstSound();
	//const 通常こちらを使う
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