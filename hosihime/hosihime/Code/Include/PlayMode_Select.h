/**
*@file PlayMode_Select.h
*@brief GamePlay‚ÌSelectMode
*author matuo
*@data 2016/6/5
*/
#ifndef _PLAYMODE_SELECT_H_
#define _PLAYMODE_SELECT_H_
#include "IPlayMode.h"
#include "StageSelect.h"
class PlayMode_Select :public IPlayMode
{
public:
	PlayMode_Select(Device& device, std::string& stageName);
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	const bool isEnd()const;
	const PLAYMODE getMode()const;
	const CLEARFLAG getFlag()const;
	const bool isLastStage()const;
private:
	StageSelect stageselect;
};
#endif
