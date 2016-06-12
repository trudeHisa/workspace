#ifndef _CIRCLEPARTICLE_H_
#define _CIRCLEPARTICLE_H_
#include "IParticle.h"
/*
*Alpha値が0になったら消える
* 円粒子クラス
*
*Effect関係の最小クラス
*/
class CircleParticle :public IParticle
{
public:
	CircleParticle(
		const std::string& textrue,const GSvector2& center,
		float speed, float angle, float alphaSpeed);
	~CircleParticle();
	void initialize();
	void update();
	void draw(const Renderer& renderer);
	const bool getIsDead()const;
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
