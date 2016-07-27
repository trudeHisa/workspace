#ifndef _FIREWORKPARTICLECONTROLLER_H_
#define _FIREWORKPARTICLECONTROLLER_H_
#include "IParticleController.h"
#include <vector>
#include "FireworkParticle.h"
class FireworkParticleController :public IParticleController
{
public:
	FireworkParticleController(const GSvector2& center);
	~FireworkParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	const bool getisEnd()const;
private:
	void createParticle();
	void remove();
private:
	std::vector<Particle_Ptr>particles;
	GSvector2 center;
};
#endif