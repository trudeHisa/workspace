#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "game.h"
#include <string>
#include <map>

#include "Renderer.h"
#include "AnimationTimer.h"
class Animation
{
public:
	Animation(AnimationTimer& timer);
	~Animation();
	void addCell(const std::string& initial,int line,int peace,int width,int heigth);
	void updata(const std::string& initial);
	void draw(const  Renderer& renderer, const std::string& name, const GSvector2* position);
private:
	const std::string createCellKey(const std::string& initial, int no)const;
private:
	AnimationTimer& timer;
	std::map<const std::string,GSrect>cells;
	std::string currentCell;
	std::string previousCell;
	int cellno;
};
#endif