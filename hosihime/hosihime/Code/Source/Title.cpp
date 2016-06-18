#include "Title.h"

#include "Calculate.h"
#include "Device.h"
#include "Star_slashdown.h"
//タイトルクラスコンストラクタ
Title::Title(Device& device)
	:device(device), rogoAlpha(0),
	control(), spawnTimer(3, 3),
	effectFactory(EffectsFactory(new EffectFactory())),
	effectController(effectFactory), timer(1, 1),
	scroll(1280, 720, GSvector2(1280, 720), 0)
{}
Title::~Title()
{
}
void Title::Init()
{
	effectFactory->addContainer();
	control.inisialize();
	effectController.initialize();

	scroll.initialize(GSvector2(0, 0));
	scroll.setMode(MODE_VERTICAL);
	
	spawnTimer.initialize();
	rogoAlpha = 0;
//	device.getSound().StopSE("Ending.wav");
	//device.getSound().PlaySE("Opening.wav");
	timer.initialize();
	alpha = 255;
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

	timer.update();
	if (timer.isEnd())
	{
		timer.initialize();
		alpha = alpha == 255 ? 0 : 255;
	}
}
void Title::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));	
	control.draw(renderer, scroll);
	effectController.draw(renderer, scroll);
	renderer.DrawTextrue("title_text.bmp", &GSvector2(200, 120), &GScolor(1, 1, 1, rogoAlpha));
	renderer.DrawTextrue("space_text.bmp", &GSvector2(480, 540), &GScolor(255, 255, 255, alpha));
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