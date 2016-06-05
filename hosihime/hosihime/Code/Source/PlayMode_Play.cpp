#include "PlayMode_Play.h"

PlayMode_Play::PlayMode_Play(Device& device, std::string& stageName)
	:stage(stageName, device)
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
}
const bool PlayMode_Play::isEnd()const
{
	return stage.getIsEnd();
}
const PLAYMODE PlayMode_Play::getMode()const
{
	return PLAYMODE::PLAY;
}