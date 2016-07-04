#ifndef _STARFADE_H_
#define _STARFADE_H_
#include "Renderer.h"

#include "StarFadeParticle.h"

#include <vector>
#include <memory>
typedef std::shared_ptr<StarFadeParticle> Fade_Ptr;
#include "Device.h"
class StarFade
{
public:
	StarFade(Device& device);
	~StarFade();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	void finish();
private:
	void createParticle();
	void remove();
private:
	std::vector< Fade_Ptr> particles;
	Device& device;
};

#endif