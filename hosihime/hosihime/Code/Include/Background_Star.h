#ifndef _BACKGROUND_STAR_H_
#define _BACKGROUND_STAR_H_

#include "GameObjControl.h"
#include "Timer.h"

#include "EffectController.h"
#include "EffectFactory.h"

class Background_Star
{
public:
	Background_Star();
	~Background_Star();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	void finish();
private:
	Timer spawnTimer;
	GameObjControl control;

	EffectsFactory effectFactory;
	EffectController effectController;
	Scroll scroll;/*É_É~Å[*/
};
#endif