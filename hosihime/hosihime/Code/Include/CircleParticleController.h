#ifndef _CIRCLEPARTICLECONTROLLER_H_
#define _CIRCLEPARTICLECONTROLLER_H_

#include "IParticleController.h"
#include"CircleParticle.h"
#include <vector>
class CircleParticleController :public IParticleController
{
public:
	CircleParticleController(const GSvector2& center);
	~CircleParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	//void setMode();
	const bool getIsEnd()const;
private:
	void createParticle();
	void remove();

private:	
	std::vector<Particle_Ptr>particles;
	GSvector2 center;
	/*
	*参照にすることで参照先の位置に追従出来る
	*ただ一時変数などを参照すると危険
	*/
	//const GSvector2& center;
};
#endif
