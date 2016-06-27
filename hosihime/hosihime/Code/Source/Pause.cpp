#include "Pause.h"
#include "Calculate.h"
#include "Device.h"
static int NowSelect = Pause_back;
Pause::Pause(Device& device)
	:device(device),index(0), isEnd(false),
	fadeIn(), fadeOut()
{
}

Pause::~Pause()
{
}

void Pause::Initializse()
{
	fadeIn.initialize();
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);
	fadeOut.initialize();

	pausecount = false;
	isEnd = false;
	index = 0;
}

void Pause::Update()
{
	PauseSwitch();

	fadeIn.updata();
	fadeOut.updata();
	if (!fadeIn.getIsEnd())
	{
		return;
	}
	/*if (!fadeOut.getIsStart())
	{
		if (!device.getInput().getActionTrigger())
		{
			return;
		}
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
	isEnd = fadeOut.getIsEnd();*/

}

void Pause::Draw(const Renderer&renderer)
{
	renderer.DrawTextrue("mapselect.bmp",&GSvector2(0,0));

	const GSvector2 ps[2] =
	{
		GSvector2(500, 500),
		GSvector2(500,600)
	};
	const std::string tex[2] =
	{
		"gamebag",
		"titlebag"
	};
	for (int i = 0; i < 2; i++)
	{
		renderer.DrawTextrue(tex[i] + "_g.bmp", &ps[i]);
	}
	renderer.DrawTextrue(tex[index] + ".bmp", &ps[index]);

	/*fadeIn.draw(renderer);
	fadeOut.draw(renderer);*/
}

void Pause::PauseSwitch()
{
	if (gsGetKeyTrigger(GKEY_B))
	pausecount = true;
}

void Pause::PauseMenu()
{
	if (gsGetJoyTrigger(0, GJOY_DOWN) || gsGetKeyTrigger(GKEY_DOWN)){
		NowSelect = (NowSelect + 1) % Pause_Num;
		index += 1;
	}

	if (gsGetJoyTrigger(0, GJOY_UP) || gsGetKeyTrigger(GKEY_UP)){
		NowSelect = (NowSelect + (Pause_Num - 1)) % Pause_Num;
		index -= 1;
	}

	Calculate<int>calc;
	index = calc.wrap(index, 0, 2);
	if (gsGetJoyTrigger(0, GJOY_BUTTON_3) || gsGetKeyTrigger(GKEY_SPACE))
	{
		
		switch (NowSelect)
		{
			//プレイ画面に戻る
		case Pause_back:
			pausecount = false;
			break;

			//タイトルに戻る
		case  Pause_title:
			isEnd = true;
			break;
		}
	}
}


void Pause::Finish()
{

}
Scene Pause::Next()
{
	return MODE_TITLE;
}
bool Pause::IsEnd()
{
	return isEnd;
}