#include "game.h"
#include <gslib.h>
#include "SceneManager.h"
#include "Load.h"
#include "Title.h"
#include "Menu.h"
#include "GamePlay.h"
#include "Ending.h"
#include "Renderer.h"
#include "Sound.h"
#include "Input.h"
SceneManager sceneManager;
Renderer renderer;
Sound sound;
Input input;
void gameInit(void)
{	
	sceneManager.Add(Scene::MODE_LOAD, new Load(renderer,&sound));
	sceneManager.Add(Scene::MODE_TITLE, new Title(input));
	sceneManager.Add(Scene::MODE_MENU,new Menu(input));
	sceneManager.Add(Scene::MODE_GAMEPLAY, new GamePlay(&sound, input));
	sceneManager.Add(Scene::MODE_ENDING, new Ending(input));
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