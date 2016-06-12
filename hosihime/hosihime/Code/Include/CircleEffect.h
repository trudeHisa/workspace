#ifndef _CIRCLEEFFECT_H_
#define _CIRCLEEFFECT_H_
#include"IEffect.h"
#include"CircleParticleController.h"

/*
*������ParticleController���Ǘ�����N���X
*(����͈�����ꍇ��vector�ŊǗ�)
*
*ParticleController��g�ݍ��킹���肵��
*Effect�ɂ���
*
*����Effect�N���X��EffectFactory�ɓo�^����
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
	void draw(const Renderer& renderer);
	void finish();
	const bool getIsEnd()const;
	IEffect* clone(const GSvector2& position);
private:
	CircleParticleController circle;
};
#endif