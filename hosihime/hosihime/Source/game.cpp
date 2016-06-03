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
#include "TimeScore.h"
SceneManager sceneManager;
Renderer renderer;
Sound sound;
Input input;
TimeScore score;
void gameInit(void)
{	
	score.init();
	sceneManager.Add(Scene::MODE_LOAD, new Load(renderer,sound));
	sceneManager.Add(Scene::MODE_TITLE, new Title(sound,input));
	sceneManager.Add(Scene::MODE_MENU,new Menu(input));
	sceneManager.Add(Scene::MODE_GAMEPLAY, new GamePlay(sound, input,score));
	sceneManager.Add(Scene::MODE_ENDING, new Ending(sound,input,score));
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