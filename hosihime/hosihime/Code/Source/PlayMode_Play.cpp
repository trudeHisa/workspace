#include "PlayMode_Play.h"

PlayMode_Play::PlayMode_Play(Device& device, std::string& stageName,TimeScore& score)
:stage(stageName, device), score(score)
{

}
void PlayMode_Play::initialize()
{
	stage.initialize();
}
void PlayMode_Play::updata()
{
	stage.updata();
}
void PlayMode_Play::draw(const Renderer& renderer)
{
	stage.draw(renderer);
}
void PlayMode_Play::finish()
{
	stage.finish();
	stage.saveScore(score);
}
const bool PlayMode_Play::isEnd()const
{
	return stage.getIsEnd();
}
const CLEARFLAG  PlayMode_Play::getFlag()const
{
	return stage.getFlag();
}

const PLAYMODE PlayMode_Play::getMode()const
{
	return PLAYMODE::PLAY;
}

const bool PlayMode_Play::isLastStage() const
{
	return false;
}