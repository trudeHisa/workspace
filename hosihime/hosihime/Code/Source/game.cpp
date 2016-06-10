#include "game.h"
#include <gslib.h>

#include "SceneManager.h"
#include "Load.h"
#include "Title.h"
#include "Menu.h"
#include "GamePlay.h"
#include "Ending.h"
#include "Result.h"
#include "Device.h"
#include "Renderer.h"
#include "TimeScore.h"
#include "GameOver.h"

SceneManager sceneManager;
Device device;
Renderer renderer;
TimeScore score;
void gameInit(void)
{	
	sceneManager.Add(Scene::MODE_LOAD, new Load(device,renderer));
	sceneManager.Add(Scene::MODE_TITLE, new Title(device));
	sceneManager.Add(Scene::MODE_MENU,new Menu(device));
	sceneManager.Add(Scene::MODE_GAMEPLAY, new GamePlay(device,score));

	sceneManager.Add(Scene::MODE_ENDING, new Ending(device,score));
	sceneManager.Add(Scene::MODE_RESULT, new Result(device, score));
	sceneManager.Add(Scene::MODE_GAMEOVER, new GameOver(device));

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