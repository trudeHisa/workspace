#ifndef _STAR_H_
#define _STAR_H_
#include <string>
#include "GameObject.h"

#include "IStarMove.h"
#include "Animation.h"
#include "IEffectMediator.h"
#include "Device.h"
class Star :virtual public GameObject
{
public:
	Star(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect,
		float helth, StarMove_Ptr move, IEffectMediator* effectMediator
		, Device& device);
	virtual ~Star();
	virtual void initialize();
	virtual void updata();
	virtual void collision(const GameObject* obj);
	virtual void draw(const Renderer& renderer, const Scroll& scroll);

	const GSvector2& getSPosi() const;
	const float getHelth()const;
	const IStarMove* getMove();

	void nonCollision();
public:
	virtual Star* clone();
	GameObject* clone(const GSvector2& position);
private:
	void rotate();
protected:
	float helth;
	float starHelth;//êØÇÃécÇËëÃóÕÇ›ÇΩÇ¢Ç»Ç‡ÇÃ
	float blinkerTime;//ì_ñ≈ä÷åWÇÃïœêî
	bool starAlpha;//êØÇÃalphaïœêî
	//Animation animation;
	//AnimationTimer animTimer;
	//int activeAnimKey;
	StarMove_Ptr move;
	float angle;//rad
	GSvector2 startPosi;

	IEffectMediator* effectMediator;
	Device& device;
};
#endif