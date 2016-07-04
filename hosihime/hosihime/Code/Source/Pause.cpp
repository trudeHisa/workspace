#include "Pause.h"
#include "Calculate.h"
#include "Device.h"
static int NowSelect = Pause_back;
Pause::Pause(Device& device)
	:device(device),index(0), 
	isEnd(false), fadeEnd(false),
	fade()
{
}

Pause::~Pause()
{
}

void Pause::Initializse()
{
	fade.initialize();
	fade.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.f);

	pausecount = false;
	isEnd = false;
	fadeEnd = false;
	index = 0;
}

void Pause::Update()
{
	PauseSwitch();

	fade.updata();
	fadeEnd = fade.getIsEnd();
	if (fade.getIsStart())
	{
		return;
	}
	if (!device.getInput().getActionTrigger())
	{
		//device.getSound().PlaySE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}

}

void Pause::Draw(const Renderer&renderer)
{
	renderer.DrawTextrue("pause.bmp", &GSvector2(0, 0),&GScolor4(0,0,0,0.5));
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
		renderer.DrawTextrue(tex[i] + "_g.bmp", &ps[i]);
	}
	renderer.DrawTextrue(tex[index] + ".bmp", &ps[index]);

	fade.draw(renderer);
}

void Pause::PauseSwitch()
{
	if (gsGetKeyTrigger(GKEY_B) || gsGetJoyTrigger(0,GJOY_BUTTON_8))
	pausecount = true;
}

void Pause::PauseMenu()
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
			pausecount = false;
			break;

			//タイトルに戻る
		case  Pause_title:
			NowSelect = 0;
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
	return Scene::MODE_TITLE;
}
bool Pause::IsEnd()
{
	return isEnd;
}