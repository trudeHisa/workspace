#ifndef _STARFADE_H_
#define _STARFADE_H_
#include "Renderer.h"

#include "StarFadeParticle.h"

#include <vector>
#include <memory>
typedef std::shared_ptr<StarFadeParticle> Fade_Ptr;
class StarFade
{
public:
	StarFade();
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
};

#endif