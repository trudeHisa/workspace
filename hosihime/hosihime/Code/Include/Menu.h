#ifndef _MENU_H_
#define _MENU_H_
#include "IScene.h"
#include "Background_Star.h"
#include "Fade.h"
class Device;
class Menu :public IScene
{
public:
	Menu(Device& device, Background_Star& bStar);
	void init();
	void update();
	void initSelect(const Input& input);
	void initDate();
	void draw(const Renderer& renderer);
	void initdraw(const Renderer& renderer);
	void finish();
	Scene next();
	bool isEnd();
private:
	Device& device;
	int index;//‘I‘ğˆŠÇ—
	bool isend;
	Background_Star& bStar;
	Fade fade;
	bool isinitDate;
	bool isinitSelect;
};

#endif