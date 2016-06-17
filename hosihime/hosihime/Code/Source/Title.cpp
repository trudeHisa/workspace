#include "Title.h"

#include "Calculate.h"
#include "Device.h"
#include "Star_slashdown.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device)
:device(device), rogoAlpha(0),
control(), spawnTimer(3, 3),
effectFactory(EffectsFactory(new EffectFactory())),
effectController(effectFactory)
{
}
Title::~Title()
{
}
void Title::Init()
{
	effectFactory->addContainer();
	control.inisialize();
	effectController.initialize();
	spawnTimer.initialize();
	rogoAlpha = 0;
	//	device.getSound().StopSE("Ending.wav");
	//device.getSound().PlaySE("Opening.wav");
	isEnd = false;
	srand((unsigned int)gsFrameTimerGetTime());

	control.add(GameObj_Ptr(new Star("star.bmp", GSvector2(rand() % 5 * 30, 0),
		GSvector2(64, 64), MyRectangle(0, 0, 64, 64), 3000,
		StarMove_Ptr(new Star_slashdown(GSvector2((rand() % 3) + 2, 5))), NULL)));
}
void Title::Update()
{

	spawnTimer.update();
	if (spawnTimer.isEnd())
	{
		control.add(GameObj_Ptr(new Star("star.bmp", GSvector2((rand() % 600), 0),
			GSvector2(64, 64), MyRectangle(0, 0, 64, 64), 3000,
			StarMove_Ptr(new Star_slashdown(GSvector2((rand() % 3) + 2, 5))), &effectController)));
		spawnTimer = Timer(0,rand()%3);
		spawnTimer.initialize();
	}
	effectController.update();

	control.updata();

	rogoAlpha += gsFrameTimerGetTime()*0.02f;
	if (rogoAlpha >= 1)
	{
		rogoAlpha = 1;
		isEnd = device.getInput().getActionTrigger();
	}

}
void Title::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	Scroll scroll = Scroll(1280, 764, GSvector2(1280, 764), 0);
	control.draw(renderer, scroll);
	effectController.draw(renderer, scroll);
	renderer.DrawTextrue("titletext.bmp", &GSvector2(200, 120), &GScolor(1, 1, 1, rogoAlpha));
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