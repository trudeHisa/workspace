/**
*@file PlayMode_Play.h
*@brief GamePlay‚ÌPlayMode
*author matuo
*@data 2016/6/5
*/
#ifndef _PLAYMODE_PLAY_H_
#define _PLAYMODE_PLAY_H_
#include "IPlayMode.h"
#include "Stage.h"
class PlayMode_Play:public IPlayMode
{
public:
	PlayMode_Play(Device& device, std::string& stageName);
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	const bool isEnd()const;
	const PLAYMODE getMode()const;
private:
	Stage stage;
};
#endif