#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Input.h"
StageSelect::StageSelect(Sound& sound,const Input& input)
	:sound(sound),input(input)
{

}
void StageSelect::initialize()
{
	active = 0;
	sound.PlaySE("Map.wav");
}
void StageSelect::updata()
{
	select();
}
void StageSelect::select()
{
	if (input.getUpTrigger())
	{
		active++;
		sound.PlaySE("cursormove.wav");
	}
	if (input.getDownTrigger())
	{
		active--;
		sound.PlaySE("cursormove.wav");
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
	return new Stage("mapdata\\\\" + datanames[active],input,sound);
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