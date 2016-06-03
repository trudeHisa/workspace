#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
#include "Sound.h"
class Stage;
class Input;
class StageSelect
{
public:
	StageSelect(Sound& sound,const Input& input);
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
	Sound& sound;
};
#endif