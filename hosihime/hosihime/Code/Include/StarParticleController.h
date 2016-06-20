#pragma once

#include "IParticleController.h"
#include "StarParticle.h"
#include "Timer.h"
#include <vector>

class StarParticleController:public IParticleController
{
public:
	StarParticleController(const GSvector2& center);
	~StarParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	const bool getIsEnd()const;
	void remove();
private:
	void createParticle();
private:
	std::vector<Particle_Ptr>Starparticles;
	//GSvector2 center;
	/*
	*参照にすることで参照先の位置に追従出来る
	*ただ一時変数などを参照すると危険
	*/
	const GSvector2& center;
    bool isEnd;
	Timer timer;
};

