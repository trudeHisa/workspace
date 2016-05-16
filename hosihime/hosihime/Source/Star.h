#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
#include "StarMediator.h"
class Star :public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2 position,StarMediator* mediator);
	~Star();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void pickUp(GSvector2* vel);
	Star* clone();
	void finish();
private:
	StarMediator* mediator;
	GSvector2 startPosi;
	//����
	void LinePattern1(GSvector2* _velocity);//�E���ɗ�����
	void LinePattern2(GSvector2* _velocity);//�����ɗ�����
	//������
	void LinePattern3(GSvector2* _velocity, float* rot);//�E��
	void LinePattern4(GSvector2* _velocity, float* rot);//����

	//�~�^��
	void LinePattern5(GSvector2* _velocity, float* rot);
	//�u�����R�݂����ȓ���
	void LinePattern6(GSvector2* _velocity, float* rot);
	//�g��
	void LinePattern7(GSvector2* _velocity, float* rot);
	float ang, spd, sindw, rot = 0;
};
#endif