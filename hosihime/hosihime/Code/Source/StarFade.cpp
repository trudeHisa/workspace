#include "StarFade.h"
#include <algorithm>
StarFade::StarFade(Device& device)
:device(device)
{

}
StarFade::~StarFade()
{

}
void StarFade::initialize()
{
	particles.clear();
	createParticle();
	device.getSound().playSE("shine1.wav");
}
void StarFade::update()
{
	for each (Fade_Ptr p in particles)
	{
		p->update();
	}
	remove();
}
void StarFade::draw(const Renderer& renderer)
{
	for each (Fade_Ptr p in particles)
	{
		p->draw(renderer);
	}
}

void StarFade::createParticle()
{
	GSvector2 offset(0, 0);

	for (int n = 0; n < 6; n++)
	{
		for (int i = 0; i < 23; i++)
		{
			offset.x = (rand() % 50) - 25 + (i * 100) + 900;
			offset.y = (rand() % 50) - 25 + (n * 150) - 1100;
			particles.emplace_back(Fade_Ptr(new StarFadeParticle(offset)));
		}
	}

}
void StarFade::remove()
{
	auto itrNewEnd = std::remove_if(particles.begin(), particles.end(), [](Fade_Ptr p)->bool
	{
		return p->getIsDead();
	});
	particles.erase(itrNewEnd, particles.end());
}
void StarFade::finish()
{
	particles.clear();
}