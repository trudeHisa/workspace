#ifndef _LIGHTPARTICLE_H_
#define _LIGHTPARTICLE_H_
#include "IParticle.h"

class LightParticle : public IParticle
{
public:
	LightParticle(
		const std::string& textrue, const GSvector2& center,
		float speed, float angle, float alphaSpeed);
	~LightParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	const bool getIsDead() const;
private:
	float speed;
	GSvector2 position;
	std::string textrue;
	float alpha;
	bool isDead;
	const float angle;//deg
	GSvector2 center;
	const float alphaSpeed;
};

#endif