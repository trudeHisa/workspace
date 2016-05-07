#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Stage;
class StageSelect
{
public:
	StageSelect();
	void initialize();
	//true�Ȃ�Stage�������ꂽ
	bool updata(Stage** stage);
	void draw(Renderer& renderer);
	void finish();
private:
	void select();
	bool stageCreate(Stage** stage);
	int active;
};
#endif