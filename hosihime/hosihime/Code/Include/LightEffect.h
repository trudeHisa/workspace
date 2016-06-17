#ifndef _LIGHTEFFECT_H_
#define _LIGHTEFFECT_H_
#include "IEffect.h"
#include "LightParticleController.h"

class LightEffect :public IEffect
{
public:
	LightEffect();
	LightEffect(const GSvector2& position);
	~LightEffect();
	void initialize();
	void update();
	void draw(const Renderer& renderer,const Scroll& scroll);
	void finish();
	const bool getIsEnd()const;
	IEffect* clone(const GSvector2& position);
private:
	LightParticleController light;

};

#endif