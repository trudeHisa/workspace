#ifndef _STAGE_H_
#define _STAGE_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "GameObjControl.h"
#include "StarManager.h"
#include "Definition.h"
#include "Scroll.h"
#include "Array2D.h"
#include "Timer.h"
#include "TimeScore.h"
class Input;
class Stage
{
public:
	Stage(const std::string& csvname,const Input& input);
	~Stage();
	void updata();
	void initialize();
	void draw(Renderer& renderer);
	void finish();
	bool getIsEnd();
	void saveScore(TimeScore& score);
private:
	void mapCreate();
	void objCreate(int x, int y, Array2D<bool>* check);
	void Stars_IsInScreen();
private:
	bool isEnd;
	Array2D<int> mapdata;	
	GameObjControl control;
	StarManger starManager;
	Scroll scroll;
	Timer timer;
	const Input& input;
};
#endif