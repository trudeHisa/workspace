#ifndef _ISCENE_H_
#define _ISCENE_H_
#include "Renderer.h"
enum Scene
{
	MODE_LOAD,
	MODE_OPENING,
	MODE_TITLE,
	MODE_GAMEPLAY,
	MODE_ENDING,
	MODE_MENU,
	MODE_CREDIT,
	MODE_OPERATION,
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