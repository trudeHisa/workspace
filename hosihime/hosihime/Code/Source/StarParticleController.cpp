#include "StarParticleController.h"
#include <algorithm>


StarParticleController::StarParticleController(const GSvector2& center)
:center(center), isEnd(false), timer(0.8,0.8)
{
}


StarParticleController::~StarParticleController()
{
}
void StarParticleController::initialize()
{
	Starparticles.clear();
	createParticle();
	isEnd = false;
	timer.initialize();
}
void StarParticleController::update()
{
	timer.update();
	createParticle();
	for each (Particle_Ptr p in Starparticles)
	{
		p->update();
	}
	remove();
	if (timer.isEnd())
	{
		isEnd = true;
	}
}
void StarParticleController::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.AdditionBlend();
	for each (Particle_Ptr p in Starparticles)
	{
		p->draw(renderer,scroll);
	}
	renderer.InitBlendFunc();
}
void StarParticleController::finish()
{

}
const bool StarParticleController::getIsEnd()const
{
	return isEnd;
}
void StarParticleController::createParticle()
{
	/*
	if (Starparticles.size() != 0)
	{
		return;
	}*/
	if (Starparticles.size() >= 40)
	{
		return;
	}
	if ((int)timer.getTime() % 3== 2)
	{
		Starparticles.emplace_back(Particle_Ptr(new StarParticle("shooting2.bmp", 0, 0.5f, center)));
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