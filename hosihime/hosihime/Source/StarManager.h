#ifndef _STARMANAGER_H_
#define _STARMANAGER_H_

#include <vector>
#include <memory>
#include"GamaObject.h"
#include"Star.h"
typedef std::vector<Star*> starsContainer;
class StarManger
{
public:
	StarManger();
	~StarManger();
	void initialize();
	void createStar();
	starsContainer& getContainer();
private:
	starsContainer stars;
};

#endif