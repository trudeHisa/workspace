#include "Ending.h"
#include "Device.h"

Ending::Ending(Device& device, TimeScore& score, StarFade& starFade)
: device(device), score(score), fadeIn(), fadeOut(),
anim(animTimer), animTimer(20.f), starFade(starFade),
isend(false)
{
}
Ending::~Ending()
{
}
void Ending::init()
{
	fadeIn.initialize();
	fadeOut.initialize();
	isend = false;
	device.getSound().playSE("ending.wav");
	playerPosi = GSvector2(1280, 200);
	logoPosi = playerPosi + GSvector2(190, 50);
	vel = GSvector2(0, 0);
	anim.addCell("A", 1, 3, 208, 204);
	animTimer.initialize();
	animTimer.setStarTimer(30.f);

	fadeIn.start(GScolor(0, 0, 0, 1), GScolor(0, 0, 0, 0), 1.0f);
}
void Ending::update()
{
	starFade.update();
	fadeIn.updata();
	if (!fadeIn.getisEnd())return;

	vel = GSvector2(-2.0f, 0);
	playerPosi += vel;
	if (playerPosi.x > 0)
	{
		logoPosi = playerPosi;
	}
	anim.updata("A");
	animTimer.updata();
	fadeOut.updata();
	isend = fadeOut.getisEnd();


	if (fadeOut.getIsStart())return;
	if (device.getInput().getActionTrigger())
	{
		fadeOut.start(GScolor(0, 0, 0, 0), GScolor(0, 0, 0, 1), 1.0f);
	}
}
void Ending::draw(const Renderer& renderer)
{
	renderer.drawTextrue("space0.bmp", &GSvector2(0, 0));
	renderer.drawTextrue("con_logo.bmp", &logoPosi,&GSvector2(2,2),&GScolor(1,1,1,1));
	anim.draw(renderer, "kasasagi_end.bmp", &playerPosi);

	if (playerPosi.x < 0)
	{
		renderer.drawString("スペースを押してね",&GSvector2(300,600),30);
	}
	fadeIn.draw(renderer);
	fadeOut.draw(renderer);
	starFade.draw(renderer);
}


void Ending::finish()
{
	device.getSound().stopSE("ending.wav");
	starFade.finish();
}
Scene Ending::next()
{
	return Scene::MODE_RESULT;
}
bool Ending::isEnd()
{
	return isend;
}