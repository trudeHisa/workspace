#include "game.h"
#include <gslib.h>

#include "SceneManager.h"
#include "Load.h"
#include "Opening.h"
#include "Title.h"
#include "Menu.h"
#include "GamePlay.h"
#include "Ending.h"
#include "Result.h"
#include "Device.h"
#include "Renderer.h"
#include "TimeScore.h"
#include "GameOver.h"
#include "Operation.h"
#include "Credit.h"
#include "Background_Star.h"

#include "StarFade.h"

SceneManager sceneManager;
Device device;
Renderer renderer;
TimeScore score;

StarFade starFade(device);
Background_Star bstar(device);
void gameInit(void)
{	
	Scene_Ptr gamePlay(new GamePlay(device, score,starFade));
	sceneManager.add(Scene::MODE_LOAD, Scene_Ptr( new Load(device, renderer)));

	sceneManager.add(Scene::MODE_OPENING, Scene_Ptr(new Opening(device)));

	sceneManager.add(Scene::MODE_TITLE, Scene_Ptr(new Title(device,bstar)));
	sceneManager.add(Scene::MODE_MENU, Scene_Ptr(new Menu(device,bstar)));

	sceneManager.add(Scene::MODE_OPERATION, Scene_Ptr(new Operation(device)));
	sceneManager.add(Scene::MODE_CREDIT, Scene_Ptr(new Credit(device)));

	sceneManager.add(Scene::MODE_GAMEPLAY, gamePlay);

	sceneManager.add(Scene::MODE_ENDING, Scene_Ptr(new Ending(device, score,starFade)));
	sceneManager.add(Scene::MODE_RESULT, Scene_Ptr(new Result(device, score, dynamic_cast<GamePlay*>(gamePlay.get()),starFade)));
	sceneManager.add(Scene::MODE_GAMEOVER, Scene_Ptr(new GameOver(device,dynamic_cast<GamePlay*>(gamePlay.get()))));

	sceneManager.change(Scene::MODE_LOAD);
}
void gameMain(void)
{	
	sceneManager.update();
}
void gameDraw(void)
{
	sceneManager.draw(renderer);
}
void gameFinish(void)
{
	sceneManager.finish();
	device.release();
}