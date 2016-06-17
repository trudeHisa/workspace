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
	particles.clear();
	createParticle();
}

void LightParticleController::update()
{
	createParticle();
	for each (Particle_Ptr p in particles)
	{
		p->update();
	}
	remove();
}

void LightParticleController::draw(const Renderer& renderer)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in particles)
	{
		p->draw(renderer);
	}
	renderer.InitBlendFunc();
}

void LightParticleController::createParticle()
{
	if (particles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <60; i++)
	{
		particles.emplace_back(Particle_Ptr(new LightParticle("lightParticle.bmp", center, 1, i*rand(), 0.02f)));
	}
}

void LightParticleController::remove()
{

}

void LightParticleController::finish()
{

}

const bool LightParticleController::getIsEnd()const
{
	return false;
}