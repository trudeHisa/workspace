#include "StageSelect.h"
#include "Stage.h"
#include "Calculate.h"
#include "Device.h"
#include "../Include/CSVStream.h"
#define STAGELENGTH 3
StageSelect::StageSelect(Device& device, int& stageNo)
	:device(device), isend(false),
	stageNo(stageNo), activeNo(0),
	fadeIn(), fadeOut(),orihimeAlpha(1.0f)
{

}
void StageSelect::initialize()
{
	activeNo = 0;
	isend = false;
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();
	device.getSound().playSE("map.wav");

	orihimeAlpha = 1.0f;

	//device.getSound().playSE("Map.wav");
	//ＣＳＶからステージの攻略状況を読み込み
	//stageLength=読み込み
	CSVStream stream;
	stream.input(activeStageLength, "savedate\\\\savedate.txt");
}
void StageSelect::updata()
{
	fadeIn.updata();
	fadeOut.updata();

	flash();

	if (!fadeIn.getisEnd())
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
		device.getSound().playSE("decision.wav");
	}

	if (fadeOut.getisEnd())
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
	if (device.getInput().getLeftTrigger() || gsGetJoyTrigger(0, GJOY_LEFT))
	{
		activeNo++;
		orihimeAlpha = 0;
		device.getSound().playSE("move.wav");
	}
	if (device.getInput().getRightTrigger() || gsGetJoyTrigger(0, GJOY_RIGHT))
	{
		activeNo--;
		orihimeAlpha = 0;
		device.getSound().playSE("move.wav");
	}
	
	Calculate<int> calc;
	activeNo = calc.wrap(activeNo, 0, activeStageLength + 1);
}

void StageSelect::draw(const Renderer& renderer)
{
	GSvector2 poss[STAGELENGTH] =
	{
		GSvector2(430, 20),
		GSvector2(110, 400),
		GSvector2(950, 440)
	};
	//マップ画像表示
	renderer.drawTextrue("mapselect.bmp", &GSvector2(0, 0));
	renderer.drawTextrue("map_title.bmp", &GSvector2(850, 30));
	renderer.drawTextrue("stage1_bega.bmp", &GSvector2(550, 30));
	renderer.drawTextrue("stage2_denebu.bmp", &GSvector2(40, 450));
	renderer.drawTextrue("stage3_artail.bmp", &GSvector2(1010, 440));
	renderer.drawTextrue("stageselect_logo.bmp", &GSvector2(100, 60));
	renderer.drawTextrue("muzukasisa.bmp", &GSvector2(300, 540));
	if (activeNo == 1)
	{
		renderer.drawTextrue("star_2.bmp", &GSvector2(632, 540));
	}
	if (activeNo == 2)
	{
		renderer.drawTextrue("star_3.bmp", &GSvector2(600, 540));
	}
	if (activeNo == 0)
	{
		renderer.drawTextrue("star_1.bmp", &GSvector2(664, 540));
	}
	renderer.drawTextrue("orihime_map.bmp", &poss[activeNo], &GScolor(1, 1, 1, orihimeAlpha));
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}
void StageSelect::finish()
{
	device.getSound().stopSE("map.wav");
}
const bool StageSelect::isLastStage()const
{
	return activeNo == STAGELENGTH - 1;
}

void StageSelect::flash()
{
	Calculate<float>calc;
	orihimeAlpha = calc.clamp(orihimeAlpha + 0.1f*gsFrameTimerGetTime(), 0, 1);
}