#include "Title.h"
//タイトルクラスコンストラクタ
#include "Point.h"
#include "Calculate.h"
#include "Input.h"
Title::Title(const Input& input)
	:input(input)
{
}
Title::~Title()
{
}
void Title::Init()
{
	index = 0;
	boolSpace = false;//「スペースキーを押してください」の管理。falseで表示
	isEnd = false;
}
void Title::Update()
{
	//メニュー選択の処理
	if (boolSpace)
	{
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
		isEnd = input.getActionTrigger();
	}

	//スペースキーを押すとメニューを表示
	if (gsGetKeyState(GKEY_SPACE) && !boolSpace){

		boolSpace = true;
	}
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titlename.bmp", &GSvector2(200, 120));
	const GSvector2 ps[3] =
	{
		GSvector2(450, 350),
		GSvector2(450, 450),
		GSvector2(450, 550)
	};
	if (!boolSpace)
	{
		renderer.DrawTextrue("spacename.bmp", &GSvector2(480, 540));
	}
	else{

		renderer.DrawTextrue("gs_g.bmp", &ps[0]);
		renderer.DrawTextrue("turt_g.bmp", &ps[1]);
		renderer.DrawTextrue("credit_g.bmp", &ps[2]);
		const std::string tex[3] =
		{
			"gs.bmp",
			"turt.bmp",
			"credit.bmp"
		};

		//現在選択しているものを表示
		renderer.DrawTextrue(tex[index], &ps[index]);
	}
}
void Title::Finish()
{
}
Scene Title::Next()
{
	Scene ns;
	switch (index)
	{
	case 0:
		//ゲームプレイへ
		ns = MODE_GAMEPLAY;
		break;
	case 1:
		//そうさせつめいへ(今はエンディングへ飛ぶ)
		ns = MODE_ENDING;
		break;
	case 2:
		//せいさくしゃ一覧へ（今はエンディングへ飛ぶ）
		ns = MODE_ENDING;
		break;
	}
	return ns;
}
bool Title::IsEnd()
{
	return isEnd;
}