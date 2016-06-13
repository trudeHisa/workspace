#ifndef _STAREFFECT_H_
#define _STAREFFECT_H_
#include"IEffect.h"
#include "StarParticleController.h"

class StarEffect :public IEffect
{
public:
	StarEffect();
	StarEffect(const GSvector2& postion);
	~StarEffect();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	const bool getIsEnd()const;
	IEffect* clone(const GSvector2& position);

private:
	StarParticleController star;
};
#endif

