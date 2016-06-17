#ifndef _TITLE_H_
#define _TITLE_H_
#include "IScene.h"
#include "GameObjControl.h"
#include "Timer.h"

#include "EffectController.h"
#include "EffectFactory.h"
class Device;
class Title :public IScene
{
public:
	Title(Device& device);
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
	Timer spawnTimer;
	GameObjControl control;

	EffectsFactory effectFactory;
	EffectController effectController;
};
#endif