#ifndef _STARFADEPARTICLE_H_
#define _STARFADEPARTICLE_H_
#include "Renderer.h"
class StarFadeParticle
{
public:
	StarFadeParticle(const GSvector2& position);
	~StarFadeParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	const bool getIsDead()const;
private:
	GSvector2 vel;
	GSvector2 position;
	float speed;
	bool isDead;
};
#endif