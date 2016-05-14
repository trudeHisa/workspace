#include "game.h"
#include <gslib.h>
#include "SceneManager.h"
#include "Load.h"
#include "Title.h"
#include "GamePlay.h"
#include "Ending.h"
#include "Renderer.h"
#include "Sound.h"
SceneManager sceneManager;
Renderer renderer;
Sound sound;
void gameInit(void)
{	
	sceneManager.Add(Scene::MODE_LOAD, new Load(renderer,&sound));
	sceneManager.Add(Scene::MODE_TITLE, new Title());
	sceneManager.Add(Scene::MODE_GAMEPLAY,new GamePlay(&sound));
	sceneManager.Add(Scene::MODE_ENDING, new Ending());
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
	renderer.Release();		
}