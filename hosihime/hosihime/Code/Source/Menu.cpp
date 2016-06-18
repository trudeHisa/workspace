#include "Menu.h"
#include "Calculate.h"
#include "Device.h"
#include "CSVStream.h"
Menu::Menu(Device& device, Background_Star& bStar)
	:device(device), index(0), bStar(bStar), fade()
{
}

void Menu::Init()
{
	fade.initialize();
	isEnd = false;
	index = 0;
}
void Menu::Update()
{
	bStar.update();
	const Input input = device.getInput();
	if (input.getUpTrigger())
	{
		index -= 1;
	}
	if (input.getDownTrigger())
	{
		index += 1;
	}
	Calculate<int>calc;
	index = calc.wrap(index, 0, 3);
	fade.updata();
	isEnd = fade.getIsEnd();
	if (fade.getIsStart())
	{
		return;
	}
	if (input.getActionTrigger())
	{
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
}
void Menu::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	bStar.draw(renderer);
	renderer.DrawTextrue("title_text.bmp", &GSvector2(200, 120));
	const GSvector2 ps[3] =
	{
		GSvector2(450, 350),
		GSvector2(450, 450),
		GSvector2(450, 550)
	};
	const std::string tex[3] =
	{
		"gamestart_text",
		"operation_text",
		"credit_text"
	};
	for (int i = 0; i < 3; i++)
	{
		renderer.DrawTextrue(tex[i] + "_gray.bmp", &ps[i]);
	}
	//現在選択しているものを表示
	renderer.DrawTextrue(tex[index] + ".bmp", &ps[index]);
	fade.draw(renderer);
}
void Menu::Finish()
{
	if (index == 0)
	{
		bStar.finish();
	}
}
Scene Menu::Next()
{
	Scene scenes[3] =
	{
		//ゲームプレイへ
		MODE_GAMEPLAY,
		//そうさせつめいへ(今はタイトルへ飛ぶ)
		MODE_OPERATION,
		//せいさくしゃ一覧へ（今はタイトルへ飛ぶ）
		MODE_CREDIT,
	};
	if (index == 2)
	{
		CSVStream stream;
		int re = 0;
		stream.output(re, "savedate\\\\savedate.txt");
	}
	return scenes[index];
}
bool Menu::IsEnd()
{
	return isEnd;
}