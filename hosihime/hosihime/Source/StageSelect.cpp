#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
StageSelect::StageSelect()
{

}
void StageSelect::initialize()
{
	active = 0;
}
bool StageSelect::updata(Stage** stage)
{
	select();
	return stageCreate(stage);
}
void StageSelect::select()
{
	if (gsGetKeyTrigger(GKEY_UP))
	{
		active++;
	}
	if (gsGetKeyTrigger(GKEY_DOWN))
	{
		active--;
	}
	Calculate<int> calc;
	active = calc.wrap(active, 0, 3);
}
bool StageSelect::stageCreate(Stage** stage)
{
	if (!gsGetKeyTrigger(GKEY_SPACE))
	{
		return false;
	}
	std::string datanames[3] =
	{
		"testmap.csv",
		"testmap.csv",
		"testmap.csv"
	};
	*stage = new Stage("mapdata\\\\" + datanames[active]);
	return true;
}
void StageSelect::draw(Renderer& renderer) 
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

void  StageSelect::debugMapCreate(Stage** stage)
{
	*stage = NULL;
	std::string datanames[3] =
	{
		"testmap.csv",
		"testmap.csv",
		"testmap.csv"
	};
	*stage = new Stage("mapdata\\\\" + datanames[active]);
}