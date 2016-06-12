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
void CircleParticleController::updata()
{
	for each (Particle_Ptr p in particles)
	{
		p->updata();
	}
	createParticle();
	remove();
}
void CircleParticleController::draw(const Renderer& renderer)
{
	for each (Particle_Ptr p in particles)
	{
		p->draw(renderer);
	}
}

void CircleParticleController::createParticle()
{
	if (particles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <360; i++)
	{
		particles.emplace_back(Particle_Ptr(new CircleParticle("circleParticle",center,5,i*rand(),10)));
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

