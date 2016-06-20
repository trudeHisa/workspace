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

SceneManager sceneManager;
Device device;
Renderer renderer;
TimeScore score;

Background_Star bstar(device);
void gameInit(void)
{	
	Scene_Ptr gamePlay(new GamePlay(device, score));
	sceneManager.Add(Scene::MODE_LOAD, Scene_Ptr( new Load(device, renderer)));

	sceneManager.Add(Scene::MODE_OPENING, Scene_Ptr(new Opening(device)));

	sceneManager.Add(Scene::MODE_TITLE, Scene_Ptr(new Title(device,bstar)));
	sceneManager.Add(Scene::MODE_MENU, Scene_Ptr(new Menu(device,bstar)));

	sceneManager.Add(Scene::MODE_OPERATION, Scene_Ptr(new Operation(device)));
	sceneManager.Add(Scene::MODE_CREDIT, Scene_Ptr(new Credit(device)));

	sceneManager.Add(Scene::MODE_GAMEPLAY, gamePlay);

	sceneManager.Add(Scene::MODE_ENDING, Scene_Ptr(new Ending(device, score)));
	sceneManager.Add(Scene::MODE_RESULT, Scene_Ptr(new Result(device, score)));
	sceneManager.Add(Scene::MODE_GAMEOVER, Scene_Ptr(new GameOver(device,dynamic_cast<GamePlay*>(gamePlay.get()))));

	sceneManager.Change(Scene::MODE_LOAD);
}
void gameMain(void)
{	
	sceneManager.Update();
}
void gameDraw(void)
{
	sceneManager.Draw(renderer);
}
void gameFinish(void)
{
	sceneManager.Finish();
	device.release();
}