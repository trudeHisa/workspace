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
	return MODE_TITLE;
}
bool Load::IsEnd()
{
	return isEnd;
}
void Load::loadTextrue()
{
	/*
	*�w�i
	*/
	std::string path = "Textrue\\\\background\\\\";
	renderer.LoadTextrue("space0.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("space1.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("space2.bmp", GS_TEXCOLOR_KEY_DISABLE, path);

	/*
	*�L�����N�^
	*/
	path = "Textrue\\\\character\\\\";
	renderer.LoadTextrue("orihime.bmp", GS_TEXCOLOR_KEY_AUTO,path);
	renderer.LoadTextrue("hikobosi.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("hold.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	/*
	*�N���W�b�g
	*/
	path = "Textrue\\\\credit\\\\";
	renderer.LoadTextrue("staffroll.bmp", GS_TEXCOLOR_KEY_DISABLE, path);

	/*
	*�Q�[���I�[�o�[
	*/
	path = "Textrue\\\\gameover\\\\";
	renderer.LoadTextrue("gameover.bmp", GS_TEXCOLOR_KEY_DISABLE,path);
	renderer.LoadTextrue("gameover_orihime.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("gameover_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*�n��
	*/
	path = "Textrue\\\\ground\\\\";
	renderer.LoadTextrue("goal.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("respawn.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("start.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("sasa.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*�J�T�T�M
	*/
	path = "Textrue\\\\magpie\\\\";
	renderer.LoadTextrue("magpie.bmp", GS_TEXCOLOR_KEY_AUTO);
	renderer.LoadTextrue("magpieEnd.bmp", GS_TEXCOLOR_KEY_AUTO);

	/*
	*�}�b�v�Z���N�g
	*/
	path = "Textrue\\\\mapselect\\\\";
	renderer.LoadTextrue("mapselect.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("orihime_map.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	
	/*
	*�i�r�Q�[�V����
	*/
	path = "Textrue\\\\navigation\\\\";
	renderer.LoadTextrue("nav.bmp", GS_TEXCOLOR_KEY_WHITE, path);

	/*
	*��Q��
	*/
	path = "Textrue\\\\obstacle\\\\";
	renderer.LoadTextrue("bigplanet.bmp", GS_TEXCOLOR_KEY_AUTO,path);
	renderer.LoadTextrue("meteo.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*�I�[�v�j���O
	*/
	path = "Textrue\\\\opening\\\\";
	renderer.LoadTextrue("opening.bmp", GS_TEXCOLOR_KEY_DISABLE, path);
	renderer.LoadTextrue("opening_text.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	
	/*
	*������@
	*/
	path = "Textrue\\\\operation\\\\";
	renderer.LoadTextrue("operation.bmp", GS_TEXCOLOR_KEY_DISABLE, path);

	/*
	*��
	*/
	path = "Textrue\\\\star\\\\";
	renderer.LoadTextrue("effect_Star.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("effect_Star_fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_break.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_fire.bmp", GS_TEXCOLOR_KEY_AUTO, path);
	renderer.LoadTextrue("star_teil.bmp", GS_TEXCOLOR_KEY_AUTO, path);

	/*
	*�^�C�g��
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



	//renderer.LoadTextrue("fireworkParticle.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("magpie.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("magpieEnd.bmp", GS_TEXCOLOR_KEY_AUTO);

	renderer.LoadTextrue("circleParticle.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("nav1.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("nav2.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("starbrun.bmp", GS_TEXCOLOR_KEY_AUTO);

	//renderer.LoadTextrue("anim.bmp");
	//renderer.LoadTextrue("orihime.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("star.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("player.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("start.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("goal.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("rock.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("rock2_2.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("planet.bmp", GS_TEXCOLOR_KEY_WHITE);

	//renderer.LoadTextrue("space0.bmp");
	//renderer.LoadTextrue("space1.bmp");
	//renderer.LoadTextrue("space2.bmp");

	//renderer.LoadTextrue("title.bmp");
	//renderer.LoadTextrue("ending.bmp");

	////���ݎg���ĂȂ��摜
	//renderer.LoadTextrue("title_logo.bmp");
	//renderer.LoadTextrue("starb.bmp", GS_TEXCOLOR_KEY_BLACK);
	//
	//renderer.LoadTextrue("sasa.bmp");
	//renderer.LoadTextrue("shooting.bmp");
	//renderer.LoadTextrue("shooting2.bmp");
	//renderer.LoadTextrue("shooting3.bmp");
	////�����܂�

	//renderer.LoadTextrue("activeselect.bmp", GS_TEXCOLOR_KEY_AUTO);
	//renderer.LoadTextrue("mapselect.bmp");

	//renderer.LoadTextrue("titletext.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("spacetext.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("gs.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("gs_g.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("operationText.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("operationText_g.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("credit.bmp", GS_TEXCOLOR_KEY_WHITE);
	//renderer.LoadTextrue("credit_g.bmp", GS_TEXCOLOR_KEY_WHITE);
}
void Load::loadSound()
{
	Sound& sound = device.getNonConstSound();
	//SE
	sound.LoadSE("Broken.wav", 5);
	sound.LoadSE("Fire.wav", 3);
	sound.LoadSE("Jump.wav", 5);
	sound.LoadSE("Landing.wav", 5);	//���n
	sound.LoadSE("cursormove.wav", 5);
	sound.LoadSE("decision.wav", 5);	//����
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