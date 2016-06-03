#ifndef _MENU_H_
#define _MENU_H_
#include "IScene.h"
class Input;
class Menu :public IScene
{
public:
	Menu(const Input& input);
	~Menu();
	void Init();
	void Update();
	void Draw(Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	const Input& input;
	int index;//‘I‘ğˆŠÇ—
	bool isEnd;
};

#endif