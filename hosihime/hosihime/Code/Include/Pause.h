#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "Renderer.h"
#include "IScene.h"
#include "Fade.h"
typedef enum
{
	Pause_back,
	Pause_title,

	Pause_Num
}pMenu;
class Device;
class Pause
{
public:
	Pause(Device& device);
	~Pause();
	void Initializse();
	void Update();
	void Draw(const Renderer&renderer);
	void PauseMenu();

	void Finish();
	Scene Next();
	bool IsEnd();
	bool pausecount;
private:
	void PauseSwitch();
	Renderer renderer;
	bool isEnd;
	bool fadeEnd;
	int index;
	Device& device;
	Fade fade;
};

#endif