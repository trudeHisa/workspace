#ifndef _CIRCLEEFFECT_H_
#define _CIRCLEEFFECT_H_
#include"IEffect.h"
#include"CircleParticleController.h"

/*
*複数のParticleControllerを管理するクラス
*(今回は一つ複数場合はvectorで管理)
*
*ParticleControllerを組み合わせたりして
*Effectにする
*
*このEffectクラスをEffectFactoryに登録する
*
*/
class CircleEffect :public IEffect
{
public:
	CircleEffect();
	CircleEffect(const GSvector2& position);
	~CircleEffect();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	const bool getisEnd()const;
	IEffect* clone(const GSvector2& position);
private:
	CircleParticleController circle;
};
#endif