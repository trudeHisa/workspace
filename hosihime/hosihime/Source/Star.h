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

	//直線
	void LinePattern1();//右下に落ちる
	void LinePattern2();//左下に落ちる
	//放物線
	void LinePattern3();//右下
	void LinePattern4();//左下

	//円運動
	void LinePattern5();
	//ブランコみたいな動き
	void LinePattern6();
	//波線
	void LinePattern7();

	void Draw(Renderer& renderer);
	void Finish();
private:
	float ang, movx, movy, spd, sindw, rot = 0;
	GSvector2 pos;
	Sound sound;
};

#endif 