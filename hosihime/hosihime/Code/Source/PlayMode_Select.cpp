#include "PlayMode_Select.h"

PlayMode_Select::PlayMode_Select(Device& device, int& stageNo)
	:stageselect(device, stageNo)
{
}
void PlayMode_Select::initialize()
{
	stageselect.initialize();
}
void PlayMode_Select::updata()
{
	stageselect.updata();
}
void PlayMode_Select::draw(const Renderer& renderer)
{
	stageselect.draw(renderer);
}
void PlayMode_Select::finish()
{
	stageselect.finish();
}
const bool PlayMode_Select::isEnd()const
{
	return stageselect.isEnd();
}
const CLEARFLAG PlayMode_Select::getFlag()const
{
	return CLEARFLAG::GAMEOVER;
}

const PLAYMODE PlayMode_Select::getMode()const
{
	return PLAYMODE::SELECT;
}

const bool PlayMode_Select::isLastStage()const
{
	return stageselect.isLastStage();
}