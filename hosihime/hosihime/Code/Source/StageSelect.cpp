#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Device.h"
#include "../Include/CSVStream.h"
#define STAGELENGTH 3
StageSelect::StageSelect(Device& device, int& stageNo)
:device(device), isend(false), stageNo(stageNo), activeNo(0)
{

}
void StageSelect::initialize()
{
	activeNo = 0;
	isend = false;
	//device.getSound().PlaySE("Map.wav");
	//ÇbÇrÇuÇ©ÇÁÉXÉeÅ[ÉWÇÃçUó™èÛãµÇì«Ç›çûÇ›
	//stageLength=ì«Ç›çûÇ›
	CSVStream stream;
	stream.input(activeStageLength, "savedate\\\\savedate.txt");
}
void StageSelect::updata()
{
	select();
	if (device.getInput().getActionTrigger())
	{
		if (activeNo <= activeStageLength)
		{
			stageNo = activeNo;
			isend = true;
		}
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
	activeNo = calc.wrap(activeNo, 0, STAGELENGTH);
}

void StageSelect::draw(const Renderer& renderer)
{
	GSvector2 poss[STAGELENGTH] =
	{
		GSvector2(190, 570),
		GSvector2(1035, 375),
		GSvector2(300, 135)
	};
	renderer.DrawTextrue("mapselect.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("activeselect.bmp", &poss[activeNo], &GScolor(1, 1, 1, 0.5f));
}
void StageSelect::finish()
{

}
const bool StageSelect::isLastStage()const
{
	return activeNo == STAGELENGTH - 1;
}