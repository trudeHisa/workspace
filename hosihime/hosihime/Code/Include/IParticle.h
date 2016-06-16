#ifndef _IPARTICLE_H_
#define _IPARTICLE_H_
#include "Renderer.h"
#include<memory>
#include "Scroll.h"
/**
*IParticle.h
*@brief IParticleクラスを実装して様々なParticleクラスをつくる
*@author matuo
*data 2016/6/12
*/
class IParticle
{
public:
	virtual ~IParticle(){}
	virtual void initialize()=0;
	virtual void update() = 0;
	virtual void draw(const Renderer& renderer, const Scroll& scroll) = 0;
	virtual const bool getIsDead()const = 0;
};
typedef std::shared_ptr<IParticle>Particle_Ptr;
#endif