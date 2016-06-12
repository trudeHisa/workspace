#ifndef _IPARTICLECONTROLLER_H_
#define _IPARTICLECONTROLLER_H_

#include <memory>
#include "IParticle.h"
typedef std::shared_ptr<IParticle> Particle_Ptr;

/**
*IParticleController.h
*@brief IParticleを管理するクラス
*@author matuo
*data 2016/6/12
*
*IParticleControllerを実装して様々な
*　Particleを管理するクラスを作る
*
*ただしpublicなadd関数は禁止(一応)
* 外部からのParticleに関する干渉をさせない
*
*常時生成、一つ消えたら一つ生成
*全て消えたら生成など様々なモードを
*選択できるようにしたかったができていない
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