#ifndef _ENDING_H_
#define _ENDING_H_
#include "IScene.h"
#include "TimeScore.h"
#include "GamePlay.h"
#include "Fade.h"
#include "Animation.h"
#include "AnimationTimer.h"
#include "StarFade.h"

class Device;
class Ending :public IScene
{
public:
	Ending(Device& device, TimeScore& score,StarFade& starFade);
	~Ending();
 	 void Init();
	 void Update();
	 void Draw(const Renderer& renderer);
	 void Finish();
	 Scene Next();
	 bool IsEnd();
private:
	bool isEnd;
	Device& device;
	TimeScore& score;
	GSvector2 playerPosi;
	GSvector2 vel;
	GSvector2 logoPosi;
	Animation anim;
	AnimationTimer animTimer;
	Fade fadeIn;
	Fade fadeOut;
	StarFade& starFade;
};
#endif