#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

#include "IStarMove.h"
class Star :virtual public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect, StarMode_Ptr move);
	virtual ~Star();
	virtual void initialize();
	virtual void updata();
	virtual void collision(const GameObject* obj);
	virtual void draw(const Renderer& renderer, const Scroll& scroll);

	const GSvector2& getSPosi() const;
public:
	void ride(GSvector2* position, const GSvector2* size)const;
	void pickUp(GSvector2* velocity)const;
	virtual Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	void rotate();
	void blurdraw(const Renderer& renderer, const GSvector2& position, const GSvector2& center);
protected:
	StarMode_Ptr move;
	float angle;//rad
	GSvector2 startPosi;
};
#endif