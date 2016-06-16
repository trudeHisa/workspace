#ifndef _FIREWORKPARTICLE_H_
#define _FIREWORKPARTICLE_H_
#include "IParticle.h"
#include "Calculate.h"
class FireworkParticle :public IParticle
{
public:
	FireworkParticle(const std::string& textrue, float angle, float speed, const GSvector2& position);
	~FireworkParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	const bool getIsDead()const;
private:
	std::string textrue;
	float rotate;
	float alpha;
	bool isDead;
	GSvector2 velocity;
	GSvector2 position;	
	const float GRAVITY;
};
#endif