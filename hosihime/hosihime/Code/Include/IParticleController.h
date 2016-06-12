#ifndef _IPARTICLECONTROLLER_H_
#define _IPARTICLECONTROLLER_H_

#include <memory>
#include "IParticle.h"
typedef std::shared_ptr<IParticle> Particle_Ptr;

/**
*IParticleController.h
*@brief IParticle���Ǘ�����N���X
*@author matuo
*data 2016/6/12
*
*IParticleController���������ėl�X��
*�@Particle���Ǘ�����N���X�����
*
*������public��add�֐��͋֎~(�ꉞ)
* �O�������Particle�Ɋւ��銱�������Ȃ�
*
*�펞�����A�������������
*�S�ď������琶���ȂǗl�X�ȃ��[�h��
*�I���ł���悤�ɂ������������ł��Ă��Ȃ�
*
*/
class IParticleController
{
public:
	virtual ~IParticleController(){}
	virtual void initialize()=0;
	virtual void update() = 0;
	virtual void draw(const Renderer& renderer) = 0;
	virtual void finish() = 0;
	//virtual void setMode() = 0;
	const virtual bool getIsEnd()const = 0;
};
#endif