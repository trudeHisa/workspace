#include "Title.h"
//タイトルクラスコンストラクタ
//testtest
Title::Title()
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
	isEnd = gsGetKeyTrigger(GKEY_SPACE);
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
}
void Title::Finish()
{
}
Scene Title::Next()
{
	return MODE_GAMEPLAY;
}
bool Title::IsEnd()
{
	return isEnd;
}