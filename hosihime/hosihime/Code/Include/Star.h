#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

#include "IStarMove.h"
class Star :public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position, const MyRectangle& rect, StarMode_Ptr move);
	~Star();
	void initialize();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);

	const GSvector2& getSPosi() const;
public:
	void ride(GSvector2* position, const GSvector2* size);
	void pickUp(GSvector2* velocity);
	Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	void rotate();
	void blurdraw(const Renderer& renderer, const GSvector2& position, const GSvector2& center);
private:
	StarMode_Ptr move;
	float angle;//rad
	GSvector2 startPosi;
};
#endif