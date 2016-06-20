#ifndef _RESULT_H_
#define _RESULT_H_
#include "IScene.h"
#include "TimeScore.h"
#include "Fade.h"
class Device;
class Result :public IScene 
{
public:
	Result(Device& device, TimeScore& score);
	~Result();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	Fade fadeIn;
	Fade fadeOut;
	Device& device;
	TimeScore& score;
};

#endif