#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_
#include "Renderer.h"
class Device;
class StageSelect
{
public:
	StageSelect(Device& device,std::string& stageName);
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	const bool isEnd()const;
private:
	const std::string selectStageName()const;
	void select();
private:
	std::string& stageName;
	bool isend;
	int active;
	Device& device;
};
#endif