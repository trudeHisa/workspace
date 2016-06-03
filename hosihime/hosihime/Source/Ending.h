#ifndef _ENDING_H_
#define _ENDING_H_
#include "IScene.h"
#include "TimeScore.h"
#include "Sound.h"
class Input;
class Ending :public IScene
{
public:
	Ending(Sound& sound, const Input& input, TimeScore& score);
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
	Sound& sound;
	TimeScore& score;
};
#endif