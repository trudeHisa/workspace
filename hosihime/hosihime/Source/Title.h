#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"
class Input;
class Title :public IScene
{
public:
	Title(const Input& input);
	~Title();
	void Init();
	void Update();
	void Draw(Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	const Input& input;
	bool isEnd;
	int index;//‘I‘ğˆŠÇ—
	bool boolSpace;//
};
#endif