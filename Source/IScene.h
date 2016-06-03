#ifndef _ISCENE_H_
#define _ISCENE_H_
#include "Renderer.h"
enum Scene
{
	MODE_LOAD,
	MODE_TITLE,
	MODE_GAMEPLAY,
	MODE_ENDING,
	MODE_MENU
};
__interface IScene
{
	 void Init() ;
	 void Update() = 0;
	 void Draw(Renderer& renderer);
	 void Finish();
	Scene Next();
	bool IsEnd();
}; 
#endif