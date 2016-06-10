#ifndef _ISCENE_H_
#define _ISCENE_H_
#include "Renderer.h"
enum Scene
{
	MODE_LOAD,
	MODE_TITLE,
	MODE_GAMEPLAY,
	MODE_ENDING,
	MODE_MENU,
	MODE_RESULT,
	MODE_GAMEOVER
};
__interface IScene
{
	 void Init() ;
	 void Update() = 0;
	 void Draw(const Renderer& renderer);
	 void Finish();
	Scene Next();
	bool IsEnd();
}; 
#endif