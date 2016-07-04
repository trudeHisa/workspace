#include "Load.h"
#include "Device.h"
#include "Renderer.h"
Load::Load(Device& device, Renderer& renderer)
:device(device), renderer(renderer)
{
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
}
void Load::Finish()
{
}
Scene Load::Next()
{
	return Scene::MODE_OPENING;
}
bool Load::IsEnd()
{
	return isEnd;
}
void Load::loadTextrue()
{
	renderer.LoadTextrue("number.bmp", GS_TEXCOLOR_KEY_AUTO);
	/*
	*背景
	*/
	std::string path = "Textrue\\\\background\\\\";
	renderer.LoadTextrue("space0.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("space1.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("space2.bmp", GS_TEXCOLOR_KEY_DISABLE, path);

	/*
	*タイマーＵＩ
	*/
	path = "Textrue\\\\obstacle\\\\";
	renderer.LoadTextrue("timer.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("timerPlanet.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*キャラクタ
	*/
	path = "Textrue\\\\character\\\\";
	renderer.LoadTextrue("orihime.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("hikobosi.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("hold.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	*クレジット
	*/
	path = "Textrue\\\\credit\\\\";
	renderer.LoadTextrue("staffroll.bmp", GS_TEXCOLOR_KEY_DISABLE, path);

	/*
	*ゲームオーバー
	*/
	path = "Textrue\\\\gameover\\\\";
	renderer.LoadTextrue("gameover.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("gameover_orihime.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("gameover_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("retry.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("titlebuck.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	*地面
	*/
	path = "Textrue\\\\ground\\\\";
	renderer.LoadTextrue("goal.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("respawn.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("start.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("sasa.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*カササギ
	*/
	path = "Textrue\\\\magpie\\\\";
	renderer.LoadTextrue("magpie.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("magpieEnd.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*マップセレクト
	*/
	path = "Textrue\\\\mapselect\\\\";
	renderer.LoadTextrue("mapselect.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("orihime_map.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("map_title.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("muzukasisa.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("stage3_artail.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("stage1_bega.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("stage2_denebu.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("stageselect_logo.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_1.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_2.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_3.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*ナビゲーション
	*/
	path = "Textrue\\\\navigation\\\\";
	renderer.LoadTextrue("nav.bmp", GS_TEXCOLOR_KEY_WHITE, path);

	/*
	*障害物
	*/
	path = "Textrue\\\\obstacle\\\\";
	renderer.LoadTextrue("bigplanet.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("meteo.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*オープニング
	*/
	path = "Textrue\\\\opening\\\\";
	renderer.LoadTextrue("opening.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("opening_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	*エンディング
	*/
	path = "Textrue\\\\ending\\\\";
	renderer.LoadTextrue("kasasagi_end.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("con_logo.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	*操作方法
	*/
	path = "Textrue\\\\operation\\\\";
	renderer.LoadTextrue("operation.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("Control.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("object.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("stage_commentary.bmp", GS_TEXCOLOR_KEY_DISABLE, path);


	/*
	*星
	*/
	path = "Textrue\\\\star\\\\";
	renderer.LoadTextrue("effect_Star.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("effect_Star_fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("teil.bmp", GS_TEXCOLOR_KEY_AUTO, path); 
	//renderer.LoadTextrue("star_break.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	アニメーションでやるつもりだったが面倒なので切り替えで
	*/
	renderer.LoadTextrue("star_break0.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_break1.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_teil.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("starg.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	
	
	/*
	*タイトル
	*/
	path = "Textrue\\\\title\\\\";
	renderer.LoadTextrue("credit_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("credit_text_gray.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("gamestart_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("gamestart_text_gray.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("operation_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("operation_text_gray.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("space_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("title_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("title.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("reset.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("reset_gray.bmp", GS_TEXCOLOR_KEY_AUTO, path);


	renderer.LoadTextrue("stage0.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("stage1.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("stage2.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("cleartime.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("secound.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("minits.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("stageClear.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("circleParticle.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("lightParticle.bmp", GS_TEXCOLOR_KEY_WHITE);
	renderer.LoadTextrue("starparticle.bmp");
	renderer.LoadTextrue("starg.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("gundam.bmp");
	renderer.LoadTextrue("shooting2.bmp");
	renderer.LoadTextrue("gamebag.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("gamebag_g.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("titlebag.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("titlebag_g.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("pause.bmp");
	renderer.LoadTextrue("yes.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("no.bmp", GS_TEXCOLOR_KEY_AUTO);

}
void Load::loadSound()
{
	Sound& sound = device.getNonConstSound();
	/*
	*SE
	*/
	std::string originalPath = "Sound\\\\SE\\\\";
	/*
	*プレイ
	*/
	std::string path = "gameplay\\\\";
	sound.LoadSE("jump.wav", 1, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("star_break.wav", 5, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("landing.wav", 5, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("star_fire.wav", 5, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("リスポーン.wav", 5, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("着地.wav", 1, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("kasasagi_fly.wav", 5, GWAVE_LOOP, originalPath + path);

	/*
	*その他
	*/
	path = "etcetera\\\\";
	sound.LoadSE("decision.wav", 1, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("move.wav", 1, GWAVE_DEFAULT, originalPath + path);
	sound.LoadSE("shine1.wav", 1, GWAVE_DEFAULT, originalPath + path);
	
	/*
	*BGM
	*/
	originalPath = "Sound\\\\BGM\\\\";
	sound.LoadSE("ending.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("gameclear0.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("gameclear1.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("gamemode0.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("gamemode1.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("gameover.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("map.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("Opening.wav", 1, GWAVE_LOOP, originalPath);
	sound.LoadSE("title.wav", 1, GWAVE_LOOP, originalPath);
}