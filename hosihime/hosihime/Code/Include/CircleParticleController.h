#ifndef _CIRCLEPARTICLECONTROLLER_H_
#define _CIRCLEPARTICLECONTROLLER_H_

#include "IParticleController.h"
#include"CircleParticle.h"
#include <vector>
class CircleParticleController :public IParticleController
{
public:
	CircleParticleController(const GSvector2& center);
	~CircleParticleController();
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	//void setMode();
	const bool getIsEnd()const;
private:
	void createParticle();
	void remove();

private:	
	std::vector<Particle_Ptr>particles;
	const GSvector2& center;
};
#endif
