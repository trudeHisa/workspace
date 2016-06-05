#include "PlayMode_Select.h"

PlayMode_Select::PlayMode_Select(Device& device, std::string& stageName)
	:stageselect(device, stageName)
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
const PLAYMODE PlayMode_Select::getMode()const
{
	return PLAYMODE::SELECT;
}