#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Stage;
class StageSelect
{
public:
	StageSelect();
	~StageSelect();
	void initialize();
	//true�Ȃ�Stage�������ꂽ
	bool updata(Stage** stage);
	void draw(Renderer& renderer);
	void finish();
private:
	GSvector2* stagePos;
	int active;
};
#endif