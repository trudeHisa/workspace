#include "Background_Star.h"
#include "Star_slashdown.h"
Background_Star::Background_Star(Device& device)
	:device(device),control(), spawnTimer(0,0),
	effectFactory(EffectsFactory(new EffectFactory())),
	effectController(effectFactory),
	scroll(1280, 720, GSvector2(1280, 720), 0)
{
}

Background_Star::~Background_Star()
{
}

void Background_Star::initialize()
{
	effectFactory->addContainer();
	control.inisialize();
	effectController.initialize();

	scroll.initialize(GSvector2(0, 0));
	scroll.setMode(MODE_VERTICAL);
	spawnTimer.initialize();

	srand((unsigned int)gsFrameTimerGetTime());
}
void Background_Star::update()
{
	spawnTimer.update();
	if (spawnTimer.isEnd())
	{
		control.add(GameObj_Ptr(new Star("star.bmp", GSvector2((rand() % 600), 0),
			GSvector2(64, 64), MyRectangle(0, 0, 64, 64), 3000,
			StarMove_Ptr(new Star_slashdown(GSvector2((rand() % 3) + 2, 5))), &effectController, device)));
		spawnTimer = Timer(0, rand() % 3);
		spawnTimer.initialize();
	}
	effectController.update();
	control.updata();
}
void Background_Star::draw(const Renderer& renderer)
{
	control.draw(renderer, scroll);
	effectController.draw(renderer, scroll);
}
void Background_Star::finish()
{
	control.finish();
	effectController.finish();
}