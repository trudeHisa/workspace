#ifndef _LIGHTPARTICLE_H_
#define _LIGHTPARTICLE_H_
#include "IParticle.h"
#include "Calculate.h"

class LightParticle : public IParticle
{
public:
	LightParticle(const std::string& textrue, float angle, float speed, const GSvector2& position);
	~LightParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	const bool getIsDead() const;
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