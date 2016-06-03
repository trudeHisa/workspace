#include "Title.h"
//タイトルクラスコンストラクタ
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
	isEnd = false;
}
void Title::Update()
{
	isEnd = input.getActionTrigger();
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titletext.bmp", &GSvector2(200, 120));
	renderer.DrawTextrue("spacetext.bmp", &GSvector2(480, 540));
}
void Title::Finish()
{
}
Scene Title::Next()
{
	return MODE_MENU;
}
bool Title::IsEnd()
{
	return isEnd;
}