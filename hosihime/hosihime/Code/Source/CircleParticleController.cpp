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
	Circleparticles.clear();
	createParticle();
}
void CircleParticleController::update()
{
	createParticle();	
	for each (Particle_Ptr p in Circleparticles)
	{
		p->update();
	}
	remove();
}
void CircleParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.additionBlend();
	for each (Particle_Ptr p in Circleparticles)
	{
		p->draw(renderer,scroll);
	}
	renderer.initBlendFunc();
}

void CircleParticleController::createParticle()
{
	if (Circleparticles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <60; i++)
	{
		Circleparticles.emplace_back(Particle_Ptr(new CircleParticle("circleParticle.bmp", center, 1, i*rand(), 0.02f)));
	}
}
void CircleParticleController::remove()
{
	auto itrNewEnd = std::remove_if(Circleparticles.begin(), Circleparticles.end(), [](Particle_Ptr p)->bool
	{
		return p->getIsDead();
	});
	Circleparticles.erase(itrNewEnd, Circleparticles.end());
}

void CircleParticleController::finish()
{
}

const bool CircleParticleController::getisEnd()const
{
	return false;
}

