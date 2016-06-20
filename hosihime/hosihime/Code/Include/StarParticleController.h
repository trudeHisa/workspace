#pragma once

#include "IParticleController.h"
#include "StarParticle.h"
#include "Timer.h"
#include <vector>

class StarParticleController:public IParticleController
{
public:
	StarParticleController(const GSvector2& center);
	~StarParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	const bool getIsEnd()const;
	void remove();
private:
	void createParticle();
private:
	std::vector<Particle_Ptr>Starparticles;
	//GSvector2 center;
	/*
	*�Q�Ƃɂ��邱�ƂŎQ�Ɛ�̈ʒu�ɒǏ]�o����
	*�����ꎞ�ϐ��Ȃǂ��Q�Ƃ���Ɗ댯
	*/
	const GSvector2& center;
    bool isEnd;
	Timer timer;
};

