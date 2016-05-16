#include "Title.h"
//タイトルクラスコンストラクタ
#include "Point.h"
int index;//選択肢管理
bool boolSpace;//
Title::Title()
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
	if (boolSpace){
		if (gsGetKeyState(GKEY_UPARROW)){
			if (gsGetKeyTrigger(GKEY_UPARROW)){
				index -= 1;
			}
		}
		if (gsGetKeyState(GKEY_DOWNARROW)){
			if (gsGetKeyTrigger(GKEY_DOWNARROW)){
				index += 1;
			}
		}
		if (index > 2)index = 0;
		if (index < 0)index = 2;
		isEnd = gsGetKeyTrigger(GKEY_SPACE);
}

	//スペースキーを押すとメニューを表示
	if (gsGetKeyState(GKEY_SPACE)&& !boolSpace){
		
		boolSpace = true;
	}
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titlename.bmp", &GSvector2(200,120));
	if (!boolSpace){
		renderer.DrawTextrue("spacename.bmp", &GSvector2(480, 540));
}
	else{
		
		renderer.DrawTextrue("gs_g.bmp", &GSvector2(450, 350));
		renderer.DrawTextrue("turt_g.bmp", &GSvector2(450, 450));
		renderer.DrawTextrue("credit_g.bmp", &GSvector2(450, 550));
		//現在選択しているものを表示
		switch (index)
		{
		case 0:
			//ゲームスタート
			renderer.DrawTextrue("gs.bmp", &GSvector2(450, 350));
			break;
		case 1:
			//そうさせつめい
			renderer.DrawTextrue("turt.bmp", &GSvector2(450, 450));
			break;
		case 2:
			//せいさくしゃ一覧
			renderer.DrawTextrue("credit.bmp", &GSvector2(450, 550));
			break;
		}
	}
}
void Title::Finish()
{
}
Scene Title::Next()
{
	
	switch (index)
	{
	case 0:
		//ゲームプレイへ
	return MODE_GAMEPLAY;
		break;
	case 1:
		//そうさせつめいへ(今はエンディングへ飛ぶ)
		return MODE_ENDING;
		break;
	case 2:
		//せいさくしゃ一覧へ（今はエンディングへ飛ぶ）
		return MODE_ENDING;
		break;
	}
	
}
bool Title::IsEnd()
{
	return isEnd;
}