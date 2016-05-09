#ifndef _STAR_H_
#define _STAR_H_
#include "GamaObject.h"
class Star:public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2* position);
	~Star();
	 void updata(MapData* mapdata);	
	 void playerPickUp(GSvector2* pos);
private:
	//����
	void LinePattern1();//�E���ɗ�����
	void LinePattern2();//�����ɗ�����
	//������
	void LinePattern3();//�E��
	void LinePattern4();//����

	//�~�^��
	void LinePattern5();
	//�u�����R�݂����ȓ���
	void LinePattern6();
	//�g��
	void LinePattern7();
	float ang, movx, movy, spd, sindw, rot = 0;
	bool collision(int nextPosType);
	void nextVelocity(GSvector2* _velocity,float* angle);
	float angle;
};
#endif