#include "StarParticleController.h"
#include <algorithm>

StarParticleController::StarParticleController(const GSvector2& center)
	:center(center)
{
}


StarParticleController::~StarParticleController()
{
}
void StarParticleController::initialize()
{
	Starparticles.clear();
	createParticle();
}
void StarParticleController::update()
{
	createParticle();
	for each (Particle_Ptr p in Starparticles)
	{
		p->update();
	}
	remove();
}
void StarParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in Starparticles)
	{
		p->draw(renderer, scroll);
	}
	renderer.InitBlendFunc();
}
void StarParticleController::finish()
{

}
const bool StarParticleController::getIsEnd()const
{
	return false;
}
void StarParticleController::createParticle()
{
	/*
	if (Starparticles.size() != 0)
	{
		return;
	}*/
	if (Starparticles.size() >= 20)
	{
		return;
	}
	//Starparticles.emplace_back(Particle_Ptr(new StarParticle("starparticle.bmp", 10*rand(), 1.5f, center)));


	for (int i = 0; i <10; i++)
	{
		Starparticles.emplace_back(Particle_Ptr(new StarParticle("starparticle.bmp", i*60, 1.0f, center)));
	}
}
void StarParticleController::remove()
{
	auto itrNewEnd = std::remove_if(Starparticles.begin(), Starparticles.end(), [](Particle_Ptr p)->bool
	{
		return p->getIsDead();
	});
	Starparticles.erase(itrNewEnd, Starparticles.end());
}