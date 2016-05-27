#ifndef _STARMANAGER_H_
#define _STARMANAGER_H_

#include <vector>
#include <memory>
#include"GameObject.h"
#include "StarMediator.h"
#include"Star.h"
typedef std::vector<Star*> starsContainer;
typedef std::vector<Star*> Stars_inScreen;
class StarManger
{
public:
	StarManger();
	~StarManger();
	void initialize(StarMediator* mediator);
	void createStarProt();
	void addInScreenStars();
	Stars_inScreen& getInScreenStars();
	void StarResporn();
private:
	StarMediator* mediator;
	starsContainer stars;//���̌��^���i�[����z��
	Stars_inScreen inScreens;//��ʓ��́����i�[����z��
};

#endif