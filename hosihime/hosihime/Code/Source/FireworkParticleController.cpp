#include "FireworkParticleController.h"
#include <algorithm>

FireworkParticleController::FireworkParticleController(const GSvector2& center)
	:center(center), particles()
{
}

FireworkParticleController::~FireworkParticleController()
{
}

void FireworkParticleController::initialize()
{
	//createParticle();
}
void FireworkParticleController::update()
{
	for each (Particle_Ptr p in particles)
	{
		p->update();
	}
	remove();
}
void FireworkParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in particles)
	{
		p->draw(renderer, scroll);
	}
	renderer.InitBlendFunc();
}
void FireworkParticleController::finish()
{

}
const bool FireworkParticleController::getIsEnd()const
{
	return particles.size() == 0;
}

void FireworkParticleController::createParticle()
{
	for (int i = 0; i <4; i++)
	{
		particles.emplace_back(Particle_Ptr(new FireworkParticle("fireworkParticle.bmp",i*90+45,2.0f, center)));
	}
}
void FireworkParticleController::remove()
{
	auto itrNewEnd = std::remove_if(particles.begin(), particles.end(), [](Particle_Ptr p)->bool
	{
		return p->getIsDead();
	});
	particles.erase(itrNewEnd, particles.end());
}