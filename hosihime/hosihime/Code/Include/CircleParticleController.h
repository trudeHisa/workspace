#ifndef _CIRCLEPARTICLECONTROLLER_H_
#define _CIRCLEPARTICLECONTROLLER_H_

#include "IParticleController.h"
#include"CircleParticle.h"
#include <vector>
/*
*Particleを管理するクラス
*
*Particleの追加と削除
*
*更新や削除が被ると思うから
*抽象クラス変えてもいいかも
*
*ParticleControllerをEffectクラスで管理
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
	*参照にすることで参照先の位置に追従出来る
	*ただ一時変数などを参照すると危険
	*/
	//const GSvector2& center;
};
#endif
