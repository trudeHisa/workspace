#include "PlayMode_Play.h"
#include "CSVStream.h"

PlayMode_Play::PlayMode_Play(Device& device, int& no, TimeScore& score, StarFade& starFade)
	:stage(no, device,starFade), score(score),
	stageNo(no)
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
	//Œ»Ý‚ÌU—ªó‹µ‚Æ”ä‚×‚Äi‚ñ‚Å‚¢‚½‚ç
	//‚b‚r‚u‚ÉƒXƒe[ƒW‚ÌU—ªó‹µ‚ð‘‚«ž‚Ý
	CSVStream stream;
	int now;
	stream.input(now, "savedate\\\\savedate.txt");
	if (stageNo >= now)
	{
		stageNo += 1;
		if (stageNo > 2)stageNo = 2;
		stream.output(stageNo, "savedate\\\\savedate.txt");
	}
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