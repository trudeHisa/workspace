#ifndef _ENDING_H_
#define _ENDING_H_
#include "IScene.h"
class Ending :public IScene
{
public:
	Ending();
	~Ending();
 	 void Init();
	 void Update();
	 void Draw(Renderer& renderer);
	 void Finish();
	 Scene Next();
	 bool IsEnd();
private:
	bool isEnd;
};
#endif