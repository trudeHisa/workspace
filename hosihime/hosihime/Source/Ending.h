#ifndef _ENDING_H_
#define _ENDING_H_
#include "IScene.h"
class Input;
class Ending :public IScene
{
public:
	Ending(const Input& input);
	~Ending();
 	 void Init();
	 void Update();
	 void Draw(Renderer& renderer);
	 void Finish();
	 Scene Next();
	 bool IsEnd();
private:
	bool isEnd;
	const Input& input;
};
#endif