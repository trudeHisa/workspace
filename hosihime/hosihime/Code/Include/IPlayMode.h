/**
*@file IPlayMode.h
*@brief GamePlay‚ÌMode
*author matuo
*@data 2016/6/5
*/
#ifndef _IPLAYMODE_H_
#define _IPLAYMODE_H_
#include "Renderer.h"
#include "CLEARFLAG.h"
enum PLAYMODE
{
	SELECT,PLAY
};
class IPlayMode
{
public:
	virtual void initialize()=0;
	virtual void updata() = 0;
	virtual void draw(const Renderer& renderer) = 0;
	virtual void finish() = 0;
	virtual const bool isEnd()const = 0;
	virtual const bool isLastStage()const=0;
	virtual const PLAYMODE getMode()const = 0;
	virtual const CLEARFLAG getFlag()const = 0;
};

#endif