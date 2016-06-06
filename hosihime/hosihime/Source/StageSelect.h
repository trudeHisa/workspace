#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Stage;
class Device;
class StageSelect
{
public:
	StageSelect(Device& device);
	void initialize();
	//trueならStage生成された
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	Stage* createStage();
private:
	void select();
private:
	int active;
	Device& device;
};
#endif