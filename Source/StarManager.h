#ifndef _STARMANAGER_H_
#define _STARMANAGER_H_

#include <vector>
#include <memory>

class StarMediator;
class Star;
class IStarMove;
#include "MyRectangle.h"
#include "Scroll.h"
typedef std::vector<Star*> starsContainer;
typedef std::vector<Star*> Stars_inScreen;
class StarManger
{
public:
	StarManger(Scroll& _scroll);
	~StarManger();
	void initialize(StarMediator* mediator);
	void createStarProt();
	void addInScreenStars();
	Stars_inScreen& getInScreenStars();
	void updata();
private:
	void starResporn();
	void remove();
	void findDeads(std::vector<Star*>* deads);
	void createData();

	IStarMove* createMove(std::vector<std::string>& param);
	MyRectangle createRect(std::vector<std::string>& param);
private:
	Scroll& scroll;
	StarMediator* mediator;
	starsContainer stars;//���̌��^���i�[����z�� instance
	Stars_inScreen inScreens;//��ʓ��́����i�[����z�� point
};

#endif