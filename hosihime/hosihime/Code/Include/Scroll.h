#ifndef _SCROLL_H_
#define _SCROLL_H_

#include "Point.h"
#include "Renderer.h"
#include "MyRectangle.h"

typedef GSvector2 SCROLL_MODE;
#define MODE_VERTICAL SCROLL_MODE(1,0)
#define MODE_HORIZONTAL SCROLL_MODE(0,1)
#define MODE_OMNIDIRECTIONAL SCROLL_MODE(1,1)
class Scroll
{
public:
	Scroll(float widht, float height, const GSvector2& maxMapSize
		,int stageNo);
	/*
	*movingAmount�̒l������
	*/
	void initialize(const GSvector2& moving);
	void draw(const Renderer& renderer);
	//Scroll����
	void moving(const GSvector2& position, const GSvector2& offset=GSvector2(0,0));
	//�E�B���h�E�̒��ɂ��邩
	const bool isInsideWindow(const GSvector2& pos, const GSvector2& size)const;
	//const GSvector2& getMovingAmount()const;
	/*
	view���W�ɕϊ�
	*/
	const GSvector2 transformViewPosition(const GSvector2& position)const;
	/*
	view����f�[�^��̍��W�ɕϊ�
	*/
	const GSvector2 transformRealPosition(const GSvector2& position)const;

	void setMode(SCROLL_MODE _mode);
	const SCROLL_MODE& getMode()const;

	void stop();
	void start();
	bool isStop();
private:
	void backGroundScroll(const GSvector2& speed);
private:
	SCROLL_MODE mode;
	bool isStart;

	GSrect s;// x
	GSrect t;// y
	GSvector2 scroll_st;//uv
	MyRectangle windowSize;
	GSvector2 movingAmount;//�ǂꂾ��Scroll������
	const GSvector2& maxMapsize;
    const int stageNo;
};
#endif