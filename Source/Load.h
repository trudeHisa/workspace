#ifndef _LOAD_H_
#define _LOAD_H_
#include "IScene.h"

#include "Sound.h"
class Load :public IScene
{
public:
	Load(Renderer& renderer,Sound* sound);
	~Load();
	void Init();
	void Update();
	void Draw(Renderer& renderer);
	void Finish();
	Scene Next();
	bool IsEnd();
private:
	bool isEnd;
	Renderer& renderer;
	Sound sound;
};
#endif