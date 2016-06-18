#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
#include "Fade.h"
#include "Timer.h"
class Device;
class StageSelect
{
public:
	StageSelect(Device& device,int& stageNo);
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	const bool isEnd()const;
	const bool isLastStage()const;
private:
	void select();
	void flash();
private:
	int& stageNo;
	bool isend;
	int activeNo;
	Device& device;
	int activeStageLength;
	Fade fadeIn;
	Fade fadeOut;
	float orihimeAlpha;
};
#endif