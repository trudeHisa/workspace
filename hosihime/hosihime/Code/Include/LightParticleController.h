#ifndef _LIGHTPARTICLECONTROLLER_H_
#define _LIGHTPARTICLECONTROLLER_H_

#include "IParticleController.h"
#include "LightParticle.h"
#include <vector>

class LightParticleController :public IParticleController
{
public:
	LightParticleController(const GSvector2& center);
	~LightParticleController();
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
	std::vector<Particle_Ptr>lightparticles;
	GSvector2 center;
	//const GSvector2& center;
};

#endif