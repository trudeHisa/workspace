#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Device.h"
StageSelect::StageSelect(Device& device)
	:device(device)
{

}
void StageSelect::initialize()
{
	active = 0;
	//device.getSound().PlaySE("Map.wav");
}
void StageSelect::updata()
{
	select();
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
	active = calc.wrap(active, 0, 3);
}

Stage* StageSelect::createStage()
{
	std::string datanames[3] =
	{
		"testmap.csv",
		"testmap.csv",
		"testmap.csv"
	};
	return new Stage("mapdata\\\\" + datanames[active],device);
}

void StageSelect::draw(const Renderer& renderer) 
{
	GSvector2 poss[3] =
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