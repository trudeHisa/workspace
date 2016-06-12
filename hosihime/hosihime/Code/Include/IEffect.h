#ifndef _IEFFECT_H_
#define _IEFFECT_H_
#include "IParticleController.h"

/**
*IEffect.h
*@brief IParticleController���Ǘ�����N���X
*@author matuo
*data 2016/6/12
*�F�X�� IParticleController���Ǘ�����
*�@�G�t�F�N�g�����
*/
#include <memory>
class IEffect
{
public:
	virtual ~IEffect(){}
	virtual void initialize() = 0;
	virtual void updata() = 0;
	virtual void draw(const Renderer& renderer) = 0;
	virtual void finish() = 0;
	virtual const bool getIsEnd()const =0;
	virtual IEffect* clone(const GSvector2& position) = 0;
};

#endif