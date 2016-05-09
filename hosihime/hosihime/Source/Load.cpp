#include "Load.h"
Load::Load(Renderer& renderer, Sound* sound)
	:renderer(renderer), sound(*sound)
{
	renderer.LoadTextrue("load.bmp");
}
Load::~Load()
{

}
void Load::Init()
{
	isEnd = false;
}
void Load::Update()
{
	renderer.LoadTextrue("star.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("player.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("title.bmp");
	renderer.LoadTextrue("gameplay.bmp");
	renderer.LoadTextrue("ending.bmp");
	renderer.LoadTextrue("space.bmp");
	renderer.LoadTextrue("rock.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("player.bmp");
	renderer.LoadTextrue("activeselect.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("stageselect.bmp");
	sound.LoadSE("testSE.wav", 5, GWAVE_LOOP);
	sound.LoadSE("testSE2.wav", 5);
	isEnd = true;
}
void Load::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("load.bmp", &GSvector2(0, 0));
}
void Load::Finish()
{
}
Scene Load::Next()
{
	return MODE_TITLE;
}
bool Load::IsEnd()
{
	return isEnd;
}