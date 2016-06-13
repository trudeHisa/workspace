#pragma once

#include "IParticleController.h"
#include "StarParticle.h"
#include <vector>

class StarParticleController:public IParticleController
{
public:
	StarParticleController(const GSvector2& center);
	~StarParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	void finish();
	const bool getIsEnd()const;
private:
	void createParticle();
	void remove();
private:
	std::vector<Particle_Ptr>Starparticles;
	GSvector2 center;
	/*
	*参照にすることで参照先の位置に追従出来る
	*ただ一時変数などを参照すると危険
	*/
	//const GSvector2& center;
};

