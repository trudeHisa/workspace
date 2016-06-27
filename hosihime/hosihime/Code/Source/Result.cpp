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

	numPositions[0][0] = GSvector2(80, 300);
	numPositions[0][1] = GSvector2(480, 300);
	numPositions[0][2] = GSvector2(580, 310);
	numPositions[0][3] = GSvector2(630, 300);
	numPositions[0][4] = GSvector2(700, 300);
	numPositions[0][5] = GSvector2(830, 310);

	numPositions[1][0] = GSvector2(80, 400);
	numPositions[1][1] = GSvector2(480, 400);
	numPositions[1][2] = GSvector2(580, 410);
	numPositions[1][3] = GSvector2(630, 400);
	numPositions[1][4] = GSvector2(700, 400);
	numPositions[1][5] = GSvector2(830, 410);

	numPositions[2][0] = GSvector2(80, 500);
	numPositions[2][1] = GSvector2(480, 500);
	numPositions[2][2] = GSvector2(580, 510);
	numPositions[2][3] = GSvector2(630, 500);
	numPositions[2][4] = GSvector2(700, 500);
	numPositions[2][5] = GSvector2(830, 510);

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
/*1,2ステージのリザルト
*/
void Result::NumDraw_Def(const Renderer& renderer, float num)
{
	renderer.DrawTextrue("cleartime.bmp", &GSvector2(100, 400));//「クリアタイム：：」
	renderer.DrawNumber("number.bmp", NUMPOSITION - GSvector2(130, 0), 80, 70, num / 60);//分単位
	renderer.DrawTextrue("minits.bmp", &(NUMPOSITION - GSvector2(30, -10)));//「分」
	renderer.DrawNumber("number.bmp", NUMPOSITION, 80, 70, num / 10);//１０の位
	renderer.DrawNumber("number.bmp", NUMPOSITION + GSvector2(70, 0), 80, 70, (int)num % 10);//１の位
	renderer.DrawTextrue("secound.bmp", &(NUMPOSITION + GSvector2(140, 10)));//「秒」
}

void Result::NumDraw_Last(const Renderer& renderer)
{
	renderer.DrawTextrue("cleartime.bmp", &GSvector2(100, 200));//「クリアタイム：：」
	
	NumDraw_One(renderer, 0);
	NumDraw_One(renderer, 1);
	NumDraw_One(renderer, 2);
}
/*最終リザルトでの１ステージごとのクリアタイム描画
*/
void Result::NumDraw_One(const Renderer& renderer,int stage)
{
	renderer.DrawTextrue("stage1.bmp", &numPositions[stage][0]);
	renderer.DrawNumber("number.bmp", numPositions[stage][1], 80, 70, scores[stage] / 60);//分単位
	renderer.DrawTextrue("minits.bmp", &numPositions[stage][2]);//「分」
	renderer.DrawNumber("number.bmp", numPositions[stage][3], 80, 70, scores[stage] / 10);//１０の位
	renderer.DrawNumber("number.bmp", numPositions[stage][4], 80, 70, (int)scores[stage] % 10);//１の位
	renderer.DrawTextrue("secound.bmp", &numPositions[stage][5]);//「秒」
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