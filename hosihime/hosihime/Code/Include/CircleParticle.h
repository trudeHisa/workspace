#ifndef _CIRCLEPARTICLE_H_
#define _CIRCLEPARTICLE_H_
#include "IParticle.h"
class CircleParticle :public IParticle
{
public:
	CircleParticle(
		const std::string& textrue,const GSvector2& center,
		float speed,float angle,float maxDistance);
	~CircleParticle();
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	const bool getIsDead()const;
private:
	float speed;
	GSvector2 position;
	std::string textrue;
	float alpha;
	bool isDead;
	const float angle;//deg
	const float maxDistance;
	const GSvector2& center;
};
#endif
