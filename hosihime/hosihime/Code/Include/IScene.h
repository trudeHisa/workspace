#ifndef _ISCENE_H_
#define _ISCENE_H_
#include "Renderer.h"
enum class Scene
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
	 void init() ;
	 void update() = 0;
	 void draw(const Renderer& renderer);
	 void finish();
	Scene next();
	bool isEnd();
}; 
#endif