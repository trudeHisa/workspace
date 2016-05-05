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
	void StarSlush();
	void Draw(Renderer& renderer);
	void Finish();
private:
	float ang;
	GSvector2 pos;
	Sound sound;
};

#endif 