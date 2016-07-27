#ifndef _CIRCLEPARTICLECONTROLLER_H_
#define _CIRCLEPARTICLECONTROLLER_H_

#include "IParticleController.h"
#include"CircleParticle.h"
#include <vector>
/*
*Particle���Ǘ�����N���X
*
*Particle�̒ǉ��ƍ폜
*
*�X�V��폜�����Ǝv������
*���ۃN���X�ς��Ă���������
*
*ParticleController��Effect�N���X�ŊǗ�
*/
class CircleParticleController :public IParticleController
{
public:
	CircleParticleController(const GSvector2& center);
	~CircleParticleController();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	//void setMode();
	const bool getisEnd()const;
private:
	void createParticle();
	void remove();

private:	
	std::vector<Particle_Ptr>Circleparticles;
	GSvector2 center;
	/*
	*�Q�Ƃɂ��邱�ƂŎQ�Ɛ�̈ʒu�ɒǏ]�o����
	*�����ꎞ�ϐ��Ȃǂ��Q�Ƃ���Ɗ댯
	*/
	//const GSvector2& center;
};
#endif
