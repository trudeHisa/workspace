#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Device.h"
#define STAGELENGTH 3
StageSelect::StageSelect(Device& device, std::string& stageName)
	:device(device), isend(false), stageName(stageName)
{

}
void StageSelect::initialize()
{
	active = 0;
	isend = false;
	//device.getSound().PlaySE("Map.wav");
}
void StageSelect::updata()
{
	select();
	if (device.getInput().getActionTrigger())
	{
		stageName = selectStageName();
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
		active++;
		device.getSound().PlaySE("cursormove.wav");
	}
	if (device.getInput().getDownTrigger())
	{
		active--;
		device.getSound().PlaySE("cursormove.wav");
	}
	Calculate<int> calc;
	active = calc.wrap(active, 0, STAGELENGTH);
}

const std::string StageSelect::selectStageName()const
{
	std::string datanames[STAGELENGTH] =
	{
		"testmap.csv",
		"testmap.csv",
		"testmap.csv"
	};
	return "mapdata\\\\" + datanames[active];
}

void StageSelect::draw(const Renderer& renderer) 
{
	GSvector2 poss[STAGELENGTH] =
	{
		GSvector2(190, 570),
		GSvector2(1035, 375),
		GSvector2(300,135)
	};
	renderer.DrawTextrue("stageselect.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("activeselect.bmp", &poss[active], &GScolor(1, 1, 1, 0.5f));
}
void StageSelect::finish()
{

}