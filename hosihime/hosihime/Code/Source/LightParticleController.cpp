#include "LightParticleController.h"
#include <algorithm>

LightParticleController::LightParticleController(const GSvector2& center)
	:center(center)
{
}

LightParticleController::~LightParticleController()
{
}

void LightParticleController::initialize()
{
	lightparticles.clear();
	createParticle();
}

void LightParticleController::update()
{
	for each (Particle_Ptr p in lightparticles)
	{
		p->update();
	}
	remove();
}

void LightParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.additionBlend();
	for each (Particle_Ptr p in lightparticles)
	{
		p->draw(renderer, scroll);
	}
	renderer.initBlendFunc();
}

void LightParticleController::createParticle()
{
	if (lightparticles.size() != 0)
	{
		return;
	}
	
	for (int i = 0; i < 6; i++)
	{
		lightparticles.emplace_back(Particle_Ptr(new LightParticle("lightParticle.bmp", i * 90, 1.5f, center)));
	}
}

void LightParticleController::remove()
{
	auto itrNewEnd = std::remove_if(lightparticles.begin(), lightparticles.end(), [](Particle_Ptr p)->bool
	{
		return p->getIsDead();
	});
	lightparticles.erase(itrNewEnd, lightparticles.end());
}

void LightParticleController::finish()
{

}

const bool LightParticleController::getisEnd()const
{
	return lightparticles.size() == 0;
}