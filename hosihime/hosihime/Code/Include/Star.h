#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

#include "IStarMove.h"
#include "Animation.h"
#include "IEffectMediator.h"
class Star :virtual public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		float helth, StarMove_Ptr move, IEffectMediator* effectMediator);
	virtual ~Star();
	virtual void initialize();
	virtual void updata();
	virtual void collision(const GameObject* obj);
	virtual void draw(const Renderer& renderer, const Scroll& scroll);

	const GSvector2& getSPosi() const;
	const float getHelth()const;
	IStarMove* getMove();
public:
	virtual Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	void rotate();
protected:
	float helth;
	float starHelth;//¯‚Ìc‚è‘Ì—Í‚İ‚½‚¢‚È‚à‚Ì
	float blinkerTime;//“_–ÅŠÖŒW‚Ì•Ï”
	bool starAlpha;//¯‚Ìalpha•Ï”
	//Animation animation;
	//AnimationTimer animTimer;
	//int activeAnimKey;
	StarMove_Ptr move;
	float angle;//rad
	GSvector2 startPosi;

	IEffectMediator* effectMediator;
};
#endif