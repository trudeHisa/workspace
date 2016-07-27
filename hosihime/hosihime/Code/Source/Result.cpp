#include "Result.h"
#include "Device.h"
#include "GamePlay.h"
#include "../Include/CSVStream.h"
#define NUMPOSITION GSvector2(480,390)
#define LASTNUMPOSITION GSvector2(480,300)
Result::Result(Device& device, TimeScore& score, GamePlay* play,StarFade& starFade)
	:device(device), score(score), fadeIn(), fadeOut(), play(play), starFade(starFade),isend(false)
{
}
Result::~Result()
{
}
void Result::init()
{
	
	fadeIn.initialize();
	fadeOut.initialize();
	isend = false;
	device.getSound().playSE("ending.wav");
	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);


	//スコアデータ読込
	CSVStream csv;
	int temp;
	csv.loadScore(temp, play->getStageNo(), "savedate////scoredate.txt");
	
	if (temp==0||temp > score.getScore())
	{
		csv.save(score.getScore(), play->getStageNo(), "savedate////scoredate.txt");
	}

	csv.loadScore(scores[0], 0, "savedate////scoredate.txt");
	csv.loadScore(scores[1], 1, "savedate////scoredate.txt");
	csv.loadScore(scores[2], 2, "savedate////scoredate.txt");

	for (int i = 0; i < 3; i++)
	{
		float y = 300 + (100 * i);
		numPositions[i][0] = GSvector2(80, y);
		for (int j = 0; j < 5; j++)
		{
			numPositions[i][j + 1] = GSvector2(520 + (80 * j), y);
		}
	}
}
void Result::update()
{
	starFade.update();
	fadeIn.updata();
	if (fadeIn.getisEnd() == false)return;

	fadeOut.updata();
	isend = fadeOut.getisEnd();

	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void Result::draw(const Renderer& renderer)
{
	renderer.drawTextrue("gameover.bmp", &GSvector2(0, 0));
	renderer.drawTextrue("stageClear.bmp", &GSvector2(100, 100));

	numDraw(renderer);

	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
	starFade.draw(renderer);
}

void Result::numDraw(const Renderer& renderer)
{
	if (play->getStageNo() != 2){
		numDraw_Def(renderer, score.getScore());
		return;
	}
	numDraw_Last(renderer);
}
/*1,2ステージのリザルト
*/
void Result::numDraw_Def(const Renderer& renderer, float num)
{
	renderer.drawTextrue("cleartime.bmp", &GSvector2(100, 400));//「クリアタイム：：」
	renderer.drawNumber("number.bmp", NUMPOSITION - GSvector2(130, 0), 80, 70, num / 60);//分単位
	renderer.drawTextrue("minits.bmp", &(NUMPOSITION - GSvector2(30, -10)));//「分」
	renderer.drawNumber("number.bmp", NUMPOSITION, 80, 70, (int)num % 60);//秒単位
	renderer.drawTextrue("secound.bmp", &(NUMPOSITION + GSvector2(140, 10)));//「秒」
}

void Result::numDraw_Last(const Renderer& renderer)
{
	renderer.drawTextrue("cleartime.bmp", &GSvector2(100, 200));//「クリアタイム：：」

	numDraw_One(renderer, 0);
	numDraw_One(renderer, 1);
	
	
	renderer.drawTextrue("stage" + std::to_string(2) + ".bmp", &numPositions[2][0]);
	renderer.drawNumber("number.bmp", numPositions[2][1], 80, 70, score.getScore() / 60);//分単位
	renderer.drawTextrue("minits.bmp", &(numPositions[2][2] + GSvector2(0, 10)));//「分」
	renderer.drawNumber("number.bmp", numPositions[2][3], 80, 70, score.getScore() % 60);//秒単位
	renderer.drawTextrue("secound.bmp", &(numPositions[2][5] + GSvector2(0, 10)));//「秒」

	
	//	numDraw_One(renderer, 2);
}
/*最終リザルトでの１ステージごとのクリアタイム描画
*/
void Result::numDraw_One(const Renderer& renderer, int stage)
{
	renderer.drawTextrue("stage" + std::to_string(stage) + ".bmp", &numPositions[stage][0]);
	renderer.drawNumber("number.bmp", numPositions[stage][1], 80, 70, scores[stage] / 60);//分単位
	renderer.drawTextrue("minits.bmp", &(numPositions[stage][2] + GSvector2(0, 10)));//「分」
	renderer.drawNumber("number.bmp", numPositions[stage][3], 80, 70, scores[stage] % 60);//秒単位
	renderer.drawTextrue("secound.bmp", &(numPositions[stage][5] + GSvector2(0, 10)));//「秒」
}

void Result::finish()
{
	starFade.finish();
}
Scene Result::next()
{
	device.getSound().stopSE("ending.wav");
	return Scene::MODE_GAMEPLAY;
}
bool Result::isEnd()
{
	return isend;
}