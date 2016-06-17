#pragma once
#include "IParticle.h"
#include "Calculate.h"

class StarParticle:public IParticle
{
public:
	StarParticle(const std::string& textrue, float angle, float speed, const GSvector2& position);
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

