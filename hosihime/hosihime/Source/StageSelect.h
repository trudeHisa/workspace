#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Stage;
class StageSelect
{
public:
	StageSelect();
	void initialize();
	//trueならStage生成された
	bool updata(Stage** stage);
	void draw(Renderer& renderer);
	void finish();

	void debugMapCreate(Stage** stage);
private:
	void select();
	bool stageCreate(Stage** stage);
	int active;
};
#endif