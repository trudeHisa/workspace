#ifndef _RESULT_H_
#define _RESULT_H_
#include "IScene.h"
#include "TimeScore.h"
#include "Fade.h"
class Device;
#include "GamePlay.h"
class Result :public IScene 
{
public:
	Result(Device& device, TimeScore& score,GamePlay* play);
	~Result();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void NumDraw(const Renderer& renderer);
	void NumDraw_Def(const Renderer& renderer, float num);
	void NumDraw_Last(const Renderer& renderer);
	void NumDraw_One(const Renderer& renderer,int stage);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	GamePlay* play;
	Fade fadeIn;
	Fade fadeOut;
	Device& device;
	TimeScore& score;
	int scores[3];
	GSvector2 numPositions[3][6];
};

#endif