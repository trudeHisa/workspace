#include "Pause.h"
#include "Calculate.h"
#include "Device.h"
static int NowSelect = Pause_back;
Pause::Pause(Device& device)
	:device(device),index(0), 
	isend(false), fadeEnd(false),
	fade(), isPause(false)
{
}

Pause::~Pause()
{
}

void Pause::initializse()
{
	fade.initialize();
	fade.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);

	isPause = false;
	isend = false;
	fadeEnd = false;
	index = 0;
}

void Pause::update()
{
	pauseSwitch();

	fade.updata();
	fadeEnd = fade.getisEnd();
	if (fade.getIsStart())
	{
		return;
	}
	if (!device.getInput().getActionTrigger())
	{
		//device.getSound().playSE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}

}

void Pause::draw(const Renderer&renderer)
{
	renderer.drawTextrue("pause.bmp", &GSvector2(0, 0),&GScolor4(0,0,0,0.5));
	const GSvector2 ps[2] =
	{
		GSvector2(450, 300),
		GSvector2(450,400)
	};
	const std::string tex[2] =
	{
		"gamebag",
		"titlebag"
	};
	for (int i = 0; i < 2; i++)
	{
		renderer.drawTextrue(tex[i] + "_g.bmp", &ps[i]);
	}
	renderer.drawTextrue(tex[index] + ".bmp", &ps[index]);

	fade.draw(renderer);
}

void Pause::pauseSwitch()
{
	if (gsGetKeyTrigger(GKEY_B) || gsGetJoyTrigger(0,GJOY_BUTTON_8))
		isPause = true;
}

void Pause::pauseMenu()
{
	if (gsGetJoyTrigger(0, GJOY_DOWN) || gsGetKeyTrigger(GKEY_DOWN)){
		// 1
		NowSelect = NowSelect + 1 % Pause_Num;
		index += 1;
	}

	if (gsGetJoyTrigger(0, GJOY_UP) || gsGetKeyTrigger(GKEY_UP)){
		// 2
		NowSelect = (NowSelect + (Pause_Num-1)) % Pause_Num;
		index -= 1;
	}

	//1と2の中身が一緒だからおかしくなってるから改善(３択なら大丈夫？)
	Calculate<int>calc;
	index = calc.wrap(index, 0, 2);
	if (gsGetJoyTrigger(0, GJOY_BUTTON_1) || gsGetKeyTrigger(GKEY_SPACE))
	{
		
		switch (NowSelect)
		{
			//プレイ画面に戻る
		case Pause_back:
			NowSelect = 0;
			isPause = false;
			break;

			//タイトルに戻る
		case  Pause_title:
			NowSelect = 0;
			isend = true;
			break;
		}
	}
}

const bool Pause::isPausing()const
{
	return isPause;
}
void Pause::finish()
{

}
Scene Pause::next()
{
	return Scene::MODE_TITLE;
}
bool Pause::isEnd()
{
	return isend;
}