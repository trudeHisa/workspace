#include "Result.h"
#include "Device.h"
#include "GamePlay.h"
#define NUMPOSITION GSvector2(480,390)
#define LASTNUMPOSITION GSvector2(480,300)
Result::Result(Device& device, TimeScore& score, GamePlay* play)
:device(device), score(score), fadeIn(), fadeOut(), play(play)
{
}
Result::~Result()
{
}
void Result::Init()
{
	fadeIn.initialize();
	fadeOut.initialize();
	isEnd = false;
	device.getSound().PlaySE("ending.wav");
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);
	scores[play->getStageNo()] = score.getScore() / FRAMETIME;

}
void Result::Update()
{
	fadeIn.updata();
	if (fadeIn.getIsEnd() == false)return;

	fadeOut.updata();
	isEnd = fadeOut.getIsEnd();

	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void Result::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("gameover.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("stageClear.bmp", &GSvector2(100, 100));

	NumDraw(renderer);

	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
}

void Result::NumDraw(const Renderer& renderer)
{
	if (play->getStageNo() != 2){
		NumDraw_Def(renderer, scores[play->getStageNo()]);
		return;
	}
	NumDraw_Last(renderer);
}

void Result::NumDraw_Def(const Renderer& renderer, float num)
{
	renderer.DrawTextrue("cleartime.bmp", &GSvector2(100, 400));//�u�N���A�^�C���F�F�v
	renderer.DrawNumber("number.bmp", NUMPOSITION - GSvector2(130, 0), 80, 70, num / 60);//���P��
	renderer.DrawTextrue("minits.bmp", &(NUMPOSITION - GSvector2(30, -10)));//�u���v
	renderer.DrawNumber("number.bmp", NUMPOSITION, 80, 70, num / 10);//�P�O�̈�
	renderer.DrawNumber("number.bmp", NUMPOSITION + GSvector2(70, 0), 80, 70, (int)num % 10);//�P�̈�
	renderer.DrawTextrue("secound.bmp", &(NUMPOSITION + GSvector2(140, 10)));//�u�b�v
}

void Result::NumDraw_Last(const Renderer& renderer)
{
	renderer.DrawTextrue("cleartime.bmp", &GSvector2(100, 200));//�u�N���A�^�C���F�F�v

	//���ā[���P
	renderer.DrawTextrue("stage1.bmp", &(LASTNUMPOSITION - GSvector2(400, 0)));
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION , 80, 70, scores[0] / 60);//���P��
	renderer.DrawTextrue("minits.bmp", &(LASTNUMPOSITION - GSvector2(-130, -10)));//�u���v
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION+GSvector2(150,0), 80, 70, scores[0] / 10);//�P�O�̈�
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION + GSvector2(220 ,0), 80, 70, (int)scores[0] % 10);//�P�̈�
	renderer.DrawTextrue("secound.bmp", &(LASTNUMPOSITION + GSvector2(350, 10)));//�u�b�v
	//�X�e�[�W�Q
	renderer.DrawTextrue("stage2.bmp", &(LASTNUMPOSITION - GSvector2(400, -100)));
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION - GSvector2(0, -100), 80, 70, scores[1] / 60);//���P��
	renderer.DrawTextrue("minits.bmp", &(LASTNUMPOSITION - GSvector2(-130, -110)));//�u���v
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION + GSvector2(150, 100), 80, 70, scores[1] / 10);//�P�O�̈�
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION + GSvector2(220, 100), 80, 70, (int)scores[1] % 10);//�P�̈�
	renderer.DrawTextrue("secound.bmp", &(LASTNUMPOSITION + GSvector2(350, 110)));//�u�b�v
	//�X�e�[�W�R
	renderer.DrawTextrue("stage3.bmp", &(LASTNUMPOSITION - GSvector2(400, -200)));
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION - GSvector2(0, -200), 80, 70, scores[2] / 60);//���P��
	renderer.DrawTextrue("minits.bmp", &(LASTNUMPOSITION - GSvector2(-130, -210)));//�u���v
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION + GSvector2(150, 200), 80, 70, (scores[2] %60)/60);//�P�O�̈�
	renderer.DrawNumber("number.bmp", LASTNUMPOSITION + GSvector2(220, 200), 80, 70, (int)scores[2] % 10);//�P�̈�
	renderer.DrawTextrue("secound.bmp", &(LASTNUMPOSITION + GSvector2(350, 210)));//�u�b�v
}
void Result::Finish()
{
}
Scene Result::Next()
{
	return MODE_GAMEPLAY;
}
bool Result::IsEnd()
{
	return isEnd;
}