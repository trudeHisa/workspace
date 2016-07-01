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
	isInitDate = false;
	index = 0;
}
void Menu::Update()
{
	bStar.update();
	const Input input = device.getInput();


	if (isInitDate){
		InitSelect(input); return;
	}


	if (input.getUpTrigger())
	{
		device.getSound().PlaySE("move.wav");
		index -= 1;
	}
	if (input.getDownTrigger())
	{
		device.getSound().PlaySE("move.wav");
		index += 1;
	}
	Calculate<int>calc;
	index = calc.wrap(index, 0, 4);
	fade.updata();
	isEnd = fade.getIsEnd();
	if (fade.getIsStart())
	{
		return;
	}

	if (input.getActionTrigger())
	{
		if (index == 3)
		{
			isInitDate = true;
			return;
		}
		device.getSound().PlaySE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
}


void Menu::InitSelect(const Input& input)
{
	if (!isInitDate)
		return;
	if (input.getLeftTrigger())
	{
		isInitSelect = !isInitSelect;
	}
	if (input.getRightTrigger())
	{
		isInitSelect = !isInitSelect;
	}

	if (input.getActionTrigger())
	{
		InitDate();
	}
}
void Menu::InitDate()
{
	if (isInitSelect)
	{
		CSVStream stream;
		int re = 0;
		stream.output(re, "savedate\\\\savedate.txt");
		for (int i = 0; i < 3; i++)
		{
			stream.save(re, i, "savedate\\\\scoredate.txt");
		}
		device.getSound().PlaySE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
		isInitDate = false;
		return;
	}
	device.getSound().PlaySE("decision.wav");
	isEnd = true;
}

void Menu::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	bStar.draw(renderer);
	renderer.DrawTextrue("title_text.bmp", &GSvector2(180, 120));
	const GSvector2 ps[4] =
	{
		GSvector2(450, 350),
		GSvector2(450, 450),
		GSvector2(450, 550),
		GSvector2(450, 650)
	};
	const std::string tex[4] =
	{
		"gamestart_text",
		"operation_text",
		"credit_text",
		"reset"
	};
	for (int i = 0; i < 4; i++)
	{
		renderer.DrawTextrue(tex[i] + "_gray.bmp", &ps[i]);
	}
	//現在選択しているものを表示
	renderer.DrawTextrue(tex[index] + ".bmp", &ps[index]);
	InitDraw(renderer);
	fade.draw(renderer);
}
void Menu::InitDraw(const Renderer& renderer)
{
	if (!isInitDate)
		return;
	renderer.DrawString("データを初期化しますか？", &GSvector2(300, 400), 40);

	GScolor yes(1, 1, 1, 1);
	GScolor no(1, 1, 1, 1);
	if (isInitSelect){
		yes = GScolor(1, 0, 0, 1);
		no = GScolor(1, 1, 1, 1);
	}
	else
	{
		yes = GScolor(1, 1, 1, 1);
		no = GScolor(1, 0, 0, 1);
	}

	renderer.DrawTextrue("minits.bmp", &GSvector2(300, 450), &yes);
	renderer.DrawTextrue("secound.bmp", &GSvector2(500, 450), &no);

}

void Menu::Finish()
{
	if (index == 0)
	{
		device.getSound().StopSE("title.wav");
		bStar.finish();
	}
}
Scene Menu::Next()
{
	Scene scenes[4] =
	{
		//ゲームプレイへ
		MODE_GAMEPLAY,
		//そうさせつめいへ(今はタイトルへ飛ぶ)
		MODE_OPERATION,
		//せいさくしゃ一覧へ（今はタイトルへ飛ぶ）
		MODE_CREDIT,
		MODE_TITLE,
	};
	if (isInitDate&&!isInitSelect){ return MODE_MENU; }
	return scenes[index];
}
bool Menu::IsEnd()
{
	return isEnd;
}