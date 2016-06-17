#ifndef _STARMANAGER_H_
#define _STARMANAGER_H_

#include <vector>

class StarMediator;
class IStarMove;
#include "MyRectangle.h"
#include "Scroll.h"
#include "GameObje_Include.h"
#include "StarFactory.h"
typedef std::vector<Star_Ptr> starsContainer;
typedef std::vector<Star_Ptr> Stars_inScreen;
typedef std::shared_ptr<StarFactory> Fact_Ptr;
typedef std::vector<Fact_Ptr> Factorys;
class IMediator;
class IEffectMediator;
class StarManger
{
public:
	StarManger(Scroll& _scroll,IMediator& mediator,IEffectMediator& effectMediator);
	~StarManger();
	void initialize();
	void createStarProt();
	void addInScreenStars();
	Stars_inScreen& getInScreenStars();
	void updata();
private:
	void starResporn();
	void remove();
	void findDeads(std::vector<Star_Ptr>* deads);
	void createData();

	Star* createStar(const std::vector<std::string>& param);
	IStarMove* createMove(const std::vector<std::string>& param, float index);
	MyRectangle createRect(const  std::vector<std::string>& param);
private:
	Scroll& scroll;
	IMediator& mediator;
	Factorys factory;
	IEffectMediator& effectMediator;
	starsContainer stars;//¯‚ÌŒ´Œ^‚ğŠi”[‚·‚é”z—ñ instance
	Stars_inScreen inScreens;//‰æ–Ê“à‚Ì™‚ğŠi”[‚·‚é”z—ñ point
};

#endif