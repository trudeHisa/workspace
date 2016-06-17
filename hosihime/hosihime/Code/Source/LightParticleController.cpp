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
	createParticle();
	for each (Particle_Ptr p in lightparticles)
	{
		p->update();
	}
	remove();
}

void LightParticleController::draw(const Renderer& renderer)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in lightparticles)
	{
		p->draw(renderer);
	}
	renderer.InitBlendFunc();
}

void LightParticleController::createParticle()
{
	if (lightparticles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <60; i++)
	{
		lightparticles.emplace_back(Particle_Ptr(new LightParticle("ligntParticle.bmp", i*rand(), 1.5f,center)));
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

const bool LightParticleController::getIsEnd()const
{
	return false;
}