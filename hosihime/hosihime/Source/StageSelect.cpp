#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
StageSelect::StageSelect()
	:stagePos(new GSvector2[3])
{

}

StageSelect::~StageSelect()
{
	delete[] stagePos;
}
void StageSelect::initialize()
{
	stagePos[0] = GSvector2(100,600);
	stagePos[1] = GSvector2(1100,300);
	stagePos[2] = GSvector2(200,100);
	active = 0;
}
bool StageSelect::updata(Stage** stage)
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
	active=calc.wrap(active,0,3);
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
	std::string name = "mapdata\\\\testmap.csv";
	*stage = new Stage(name);
	return true;
}
void StageSelect::draw(Renderer& renderer) 
{
	renderer.DrawTextrue("space.bmp", &GSvector2(0,0));
	for (int i = 0; i <3; i++)
	{
		renderer.DrawTextrue("select.bmp",&stagePos[i]);
	}
	GSvector2 selectPos = stagePos[active] - GSvector2(8,8);
	renderer.DrawTextrue("activeselect.bmp", &selectPos,&GScolor(1,1,1,0.5f));
	
}
void StageSelect::finish()
{

}