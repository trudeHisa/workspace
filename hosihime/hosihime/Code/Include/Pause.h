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
	void initializse();
	void update();
	void draw(const Renderer&renderer);
	void pauseMenu();
	const bool isPausing()const;
	void finish();
	Scene next();
	bool isEnd();
	
private:
	void pauseSwitch();
private:
	
	Renderer renderer;
	bool isend;
	bool fadeEnd;
	bool isPause;
	int index;
	Device& device;
	Fade fade;
};

#endif