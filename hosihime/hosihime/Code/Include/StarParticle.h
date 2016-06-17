#pragma once
#include "IParticle.h"
class StarParticle:public IParticle
{
public:
	StarParticle(const std::string& textrue, const GSvector2& center,
		float speed, float angle, float alphaSpeed);
	~StarParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
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

