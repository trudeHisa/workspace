#ifndef _PLAYENDPARTICLE_H_
#define _PLAYENDPARTICLE_H_
#include "IParticle.h"
class PlayEndParticle
{
public:
	PlayEndParticle();
	~PlayEndParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	const bool getIsDead()const;
private:
	static const GSvector2 MAXWINDOW;//const GSvector2 PlayEndParticle::MAXWINDOW =GSvector2(0,0);
	GSvector2 vel;
	GSvector2 position;
	float speed;

};

PlayEndParticle::PlayEndParticle()
{
}

PlayEndParticle::~PlayEndParticle()
{
}

#endif