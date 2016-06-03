#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Stage;
class Input;
class StageSelect
{
public:
	StageSelect(const Input& input);
	void initialize();
	//true�Ȃ�Stage�������ꂽ
	void updata();
	void draw(Renderer& renderer);
	void finish();
	Stage* createStage();
private:
	void select();
	const Input& input;
	int active;
};
#endif