#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"
#include "Timer.h"
#include "Background_Star.h"

class Device;
class Title :public IScene
{
public:
	Title(Device& device, Background_Star& bStar);
	~Title();
	void Init();
	void Update();
	void Draw(const Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	Timer timer;
	float alpha;
	float rogoAlpha;
	
	Device& device;
	bool isEnd;
	int index;//ëIëéàä«óù
	bool boolSpace;//

	Background_Star& bStar;
};
#endif