#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

#include "IStarMove.h"
#include "Animation.h"
class Star :virtual public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,StarMove_Ptr move
		, float helth);
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
	float helth;
	float starHelth;//星の残り体力みたいなもの
	float blinkerTime;//点滅関係の変数
	bool starAlpha;//星のalpha変数
	//Animation animation;
	//AnimationTimer animTimer;
	//int activeAnimKey;
	StarMove_Ptr move;
	float angle;//rad
	GSvector2 startPosi;
};
#endif