#ifndef _FIREWORKEFFECT_H_
#define _FIREWORKEFFECT_H_
#include"IEffect.h"
#include "FireworkParticleController.h"
class FireworkEffect :public IEffect
{
public:
	FireworkEffect();
	FireworkEffect(const GSvector2& position);
	~FireworkEffect();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	const bool getIsEnd()const;
	IEffect* clone(const GSvector2& position);
private:
	FireworkParticleController firework;
};
#endif