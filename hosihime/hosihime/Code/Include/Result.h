#ifndef _RESULT_H_
#define _RESULT_H_
#include "IScene.h"
#include "TimeScore.h"
#include "Fade.h"
class Device;
#include "GamePlay.h"

#include "StarFade.h"
class Result :public IScene 
{
public:
	Result(Device& device, TimeScore& score, GamePlay* play, StarFade& starFade);
	~Result();
	void init();
	void update();
	void draw(const Renderer& renderer);
	void numDraw(const Renderer& renderer);
	void numDraw_Def(const Renderer& renderer, float num);
	void numDraw_Last(const Renderer& renderer);
	void numDraw_One(const Renderer& renderer,int stage);
	void finish();
	Scene next();
	bool isEnd();
private:
	bool isend;
	GamePlay* play;
	Fade fadeIn;
	Fade fadeOut;
	Device& device;
	TimeScore& score;
	int scores[3];
	GSvector2 numPositions[3][6];
	StarFade& starFade;
};

#endif