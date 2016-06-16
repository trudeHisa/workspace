#include"CircleParticleController.h"
#include <algorithm>
CircleParticleController::CircleParticleController(const GSvector2& center)
	:center(center)
{
}

CircleParticleController::~CircleParticleController()
{
}

void CircleParticleController::initialize()
{
	particles.clear();
	createParticle();
}
void CircleParticleController::update()
{
	createParticle();	
	for each (Particle_Ptr p in particles)
	{
		p->update();
	}
	remove();
}
void CircleParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in particles)
	{
		p->draw(renderer,scroll);
	}
	renderer.InitBlendFunc();
}

void CircleParticleController::createParticle()
{
	if (particles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <60; i++)
	{
		particles.emplace_back(Particle_Ptr(new CircleParticle("circleParticle.bmp", center, 1, i*rand(), 0.02f)));
	}
}
void CircleParticleController::remove()
{
	auto itrNewEnd = std::remove_if(particles.begin(), particles.end(), [](Particle_Ptr p)->bool
	{
		return p->getIsDead();
	});
	particles.erase(itrNewEnd, particles.end());
}

void CircleParticleController::finish()
{
}

const bool CircleParticleController::getIsEnd()const
{
	return false;
}

