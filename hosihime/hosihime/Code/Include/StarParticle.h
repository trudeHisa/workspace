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
	float speed;
	bool isDead;
	GSvector2 position;
	std::string textrue;
	float alpha;
	const float angle;
	const float alphaSpeed;
	GSvector2 center;
	float a;
	float b;
};

