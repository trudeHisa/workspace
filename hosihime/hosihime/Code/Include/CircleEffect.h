#ifndef _CIRCLEEFFECT_H_
#define _CIRCLEEFFECT_H_
#include"IEffect.h"
#include"CircleParticleController.h"
class CircleEffect :public IEffect
{
public:
	CircleEffect();
	CircleEffect(const GSvector2& position);
	~CircleEffect();
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	const bool getIsEnd()const;
	IEffect* clone(const GSvector2& position);
private:
	CircleParticleController circle;
};
#endif