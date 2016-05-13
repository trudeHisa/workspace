#include "StarManager.h"

StarManger::StarManger()
{
}
StarManger::~StarManger()
{
}
void StarManger::initialize()
{
	stars.clear();
}
//ÉXÉ^Å[ê∂ê¨
void StarManger::createStar()
{
	stars.push_back(new Star("star.bmp", GSvector2(100, 100)));
	stars.push_back(new Star("star.bmp", GSvector2(100, 200)));
}

starsContainer& StarManger::getContainer()
{
	return stars;
}