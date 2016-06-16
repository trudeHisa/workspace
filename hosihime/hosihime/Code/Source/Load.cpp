#include "Load.h"
#include "Device.h"
#include "Renderer.h"
Load::Load(Device& device, Renderer& renderer)
	:device(device), renderer(renderer)
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
	loadTextrue();
	loadSound();

	isEnd = true;
}
void Load::Draw(const Renderer& renderer)
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
void Load::loadTextrue()
{
	renderer.LoadTextrue("fireworkParticle.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("magpie.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("magpieEnd.bmp", GS_TEXCOLOR_KEY_AUTO);

	renderer.LoadTextrue("circleParticle.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("nav1.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("nav2.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("starbrun.bmp", GS_TEXCOLOR_KEY_AUTO);

	renderer.LoadTextrue("anim.bmp");
	renderer.LoadTextrue("orihime.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("star.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("player.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("start.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("goal.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("rock.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("rock2_2.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("planet.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("space.bmp");
	renderer.LoadTextrue("space2.bmp");
	renderer.LoadTextrue("title.bmp");
	renderer.LoadTextrue("ending.bmp");

	//åªç›égÇ¡ÇƒÇ»Ç¢âÊëú
	renderer.LoadTextrue("title_logo.bmp");
	renderer.LoadTextrue("starb.bmp", GS_TEXCOLOR_KEY_BLACK);
	renderer.LoadTextrue("space3.bmp");
	renderer.LoadTextrue("sasa.bmp");
	renderer.LoadTextrue("shooting.bmp");
	renderer.LoadTextrue("shooting2.bmp");
	renderer.LoadTextrue("shooting3.bmp");
	//Ç±Ç±Ç‹Ç≈

	renderer.LoadTextrue("activeselect.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("stageselect.bmp");

	renderer.LoadTextrue("titletext.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("spacetext.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("gs.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("gs_g.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("operationText.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("operationText_g.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("credit.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("credit_g.bmp", GS_TEXCOLOR_KEY_WHITE);
}
void Load::loadSound()
{
	Sound& sound = device.getNonConstSound();
	//SE
	sound.LoadSE("Broken.wav", 5);
	sound.LoadSE("Fire.wav", 3);
	sound.LoadSE("Jump.wav", 5);
	sound.LoadSE("Landing.wav", 5);	//íÖín
	sound.LoadSE("cursormove.wav", 5);
	sound.LoadSE("decision.wav", 5);	//åàíË
	//BGM
	std::string path = "Sound\\\\BGM\\\\";
	sound.LoadSE("Clear_1.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Clear_2.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Ending.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Opening.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("GameMode_1.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("GameMode_2.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Gameover.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Map.wav", 5, GWAVE_LOOP, path);
	sound.LoadSE("Title.wav", 5, GWAVE_LOOP, path);
}