#include "Menu.h"
#include "Calculate.h"
#include "Device.h"
#include "CSVStream.h"
Menu::Menu(Device& device, Background_Star& bStar)
	:device(device), index(0), bStar(bStar), fade(), isend(false)
{
}

void Menu::init()
{
	fade.initialize();
	isend = false;
	isinitDate = false;
	index = 0;
}
void Menu::update()
{
	bStar.update();
	const Input input = device.getInput();


	if (isinitDate){
		initSelect(input); return;
	}


	if (input.getUpTrigger())
	{
		device.getSound().playSE("move.wav");
		index -= 1;
	}
	if (input.getDownTrigger())
	{
		device.getSound().playSE("move.wav");
		index += 1;
	}
	Calculate<int>calc;
	index = calc.wrap(index, 0, 4);
	fade.updata();
	isend = fade.getisEnd();
	if (fade.getIsStart())
	{
		return;
	}

	if (input.getActionTrigger())
	{
		if (index == 3)
		{
			isinitDate = true;
			return;
		}
		device.getSound().playSE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
	}
}


void Menu::initSelect(const Input& input)
{
	if (!isinitDate)
		return;
	if (input.getLeftTrigger())
	{
		isinitSelect = !isinitSelect;
	}
	if (input.getRightTrigger())
	{
		isinitSelect = !isinitSelect;
	}

	if (input.getActionTrigger())
	{
		initDate();
	}
}
void Menu::initDate()
{
	if (isinitSelect)
	{
		CSVStream stream;
		int re = 0;
		stream.output(re, "savedate\\\\savedate.txt");
		for (int i = 0; i < 3; i++)
		{
			stream.save(re, i, "savedate\\\\scoredate.txt");
		}
		device.getSound().playSE("decision.wav");
		fade.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.f);
		isinitDate = false;
		return;
	}
	device.getSound().playSE("decision.wav");
	isend = true;
}

void Menu::draw(const Renderer& renderer)
{
	renderer.drawTextrue("title.bmp", &GSvector2(0, 0));
	bStar.draw(renderer);
	renderer.drawTextrue("title_text.bmp", &GSvector2(180, 120));
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
		renderer.drawTextrue(tex[i] + "_gray.bmp", &ps[i]);
	}
	//現在選択しているものを表示
	renderer.drawTextrue(tex[index] + ".bmp", &ps[index]);
	initdraw(renderer);
	fade.draw(renderer);
}
void Menu::initdraw(const Renderer& renderer)
{
	if (!isinitDate)
		return;
	renderer.drawTextrue("pause.bmp",&GSvector2(0,0),&GScolor(1,1,1,0.6));
	renderer.drawString("データを初期化しますか？", &GSvector2(400, 400), 50,&GScolor(1,1,0,1),GS_FONT_BOLD,"メイリオ");

	GScolor yes(1, 1, 1, 1);
	GScolor no(1, 1, 1, 1);
	GSvector2 s_yes(1, 1);
	GSvector2 s_no(1, 1);
	if (isinitSelect){
		yes = GScolor(1, 0, 0, 1);
		no = GScolor(1, 1, 1, 1);
		s_yes = GSvector2(1.2, 1.2);
		s_no = GSvector2(1, 1);
	}
	else
	{
		yes = GScolor(1, 1, 1, 1);
		no = GScolor(1, 0, 0, 1);
		s_yes = GSvector2(1, 1);
		s_no = GSvector2(1.2, 1.2);
	}

	renderer.drawTextrue("yes.bmp", &GSvector2(400, 450),&s_yes,&yes);
	renderer.drawTextrue("no.bmp", &GSvector2(600, 450), &s_no,&no);

}

void Menu::finish()
{
	if (index == 0)
	{
		device.getSound().stopSE("title.wav");
		bStar.finish();
	}
}
Scene Menu::next()
{
	Scene scenes[4] =
	{
		//ゲームプレイへ
		Scene::MODE_GAMEPLAY,
		//そうさせつめいへ(今はタイトルへ飛ぶ)
		Scene::MODE_OPERATION,
		//せいさくしゃ一覧へ（今はタイトルへ飛ぶ）
		Scene::MODE_CREDIT,
		Scene::MODE_TITLE,
	};
	if (isinitDate&&!isinitSelect){ return Scene::MODE_MENU; }
	return scenes[index];
}
bool Menu::isEnd()
{
	return isend;
}