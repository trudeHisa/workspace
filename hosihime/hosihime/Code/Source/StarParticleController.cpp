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
void StarParticleController::draw(const Renderer& renderer)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in Starparticles)
	{
		p->draw(renderer);
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
	if (Starparticles.size() != 0)
	{
		return;
	}
	for (int i = 0; i <60; i++)
	{
		Starparticles.emplace_back(Particle_Ptr(new StarParticle("starparticle.bmp", center, 1, i*rand(), 0.02f)));
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