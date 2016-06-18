#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Device.h"
#include "../Include/CSVStream.h"
#define STAGELENGTH 3
StageSelect::StageSelect(Device& device, int& stageNo)
	:device(device), isend(false), 
	stageNo(stageNo), activeNo(0),
	fadeIn(), fadeOut()
{

}
void StageSelect::initialize()
{
	activeNo = 0;
	isend = false;

	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();

	//device.getSound().PlaySE("Map.wav");
	//ÇbÇrÇuÇ©ÇÁÉXÉeÅ[ÉWÇÃçUó™èÛãµÇì«Ç›çûÇ›
	//stageLength=ì«Ç›çûÇ›
	CSVStream stream;
	stream.input(activeStageLength, "savedate\\\\savedate.txt");
}
void StageSelect::updata()
{
	fadeIn.updata();
	fadeOut.updata();
	if (!fadeIn.getIsEnd())
	{
		return;
	}

	if (!fadeOut.getIsStart())
	{
		select();
		if (!device.getInput().getActionTrigger())
		{
			return;
		}
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}

	if (fadeOut.getIsEnd())
	{
		stageNo = activeNo;
		isend = true;
	}
}
const bool StageSelect::isEnd()const
{
	return isend;
}
void StageSelect::select()
{
	if (device.getInput().getUpTrigger())
	{
		activeNo++;
		device.getSound().PlaySE("cursormove.wav");
	}
	if (device.getInput().getDownTrigger())
	{
		activeNo--;
		device.getSound().PlaySE("cursormove.wav");
	}
	Calculate<int> calc;
 	activeNo = calc.wrap(activeNo, 0, activeStageLength+1);
}

void StageSelect::draw(const Renderer& renderer)
{
	GSvector2 poss[STAGELENGTH] =
	{
		GSvector2(430, 20),
		GSvector2(110, 400),
		GSvector2(950, 440)
	};
	renderer.DrawTextrue("mapselect.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("orihime_map.bmp", &poss[activeNo], &GScolor(1, 1, 1, 0.5f));
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void StageSelect::finish()
{

}
const bool StageSelect::isLastStage()const
{
	return activeNo == STAGELENGTH - 1;
}