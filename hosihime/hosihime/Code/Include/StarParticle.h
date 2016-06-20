#pragma once
#include "IParticle.h"
#include "Calculate.h"
#include <random>


class StarParticle:public IParticle
{
public:
	StarParticle(const std::string& textrue, float angle, float speed, const GSvector2& position);
	~StarParticle();
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
	std::mt19937 mt;
	std::random_device rnd;
	std::uniform_int_distribution<> rand;
};

