#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"

class Title :public IScene
{
public:
	Title();
	~Title();
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