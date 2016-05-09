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

	//’¼ü
	void LinePattern1();//‰E‰º‚É—‚¿‚é
	void LinePattern2();//¶‰º‚É—‚¿‚é
	//•ú•¨ü
	void LinePattern3();//‰E‰º
	void LinePattern4();//¶‰º
	//‰~‰^“®
	void LinePattern5();
	//ƒuƒ‰ƒ“ƒR‚İ‚½‚¢‚È“®‚«
	void LinePattern6();
	//”gü
	void LinePattern7();

	void Draw(Renderer& renderer);
	void Finish();
private:
	float ang, movx, movy, spd, sindw, rot = 0;
	GSvector2 pos;
	Sound sound;
};

#endif 