#ifndef _STAR_H_
#define _STAR_H_
#include "Renderer.h"
#include "Sound.h"
class Star
{
public:
	Star();
	~Star();
	void Init();

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

	void Draw(Renderer& renderer);
	void Finish();
private:
	float ang, movx, movy, spd, sindw, rot = 0;
	GSvector2 pos;
	Sound sound;
};

#endif 