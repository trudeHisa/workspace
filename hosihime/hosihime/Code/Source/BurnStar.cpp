#include "BurnStar.h"

BurnStar::BurnStar(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect,
	float helth, StarMove_Ptr move,IEffectMediator* effectMediator
	, Device& device)
	:GameObject(textrue, position, viewSize, rect, BURNSTAR),
	Star(textrue, position, viewSize, rect, helth, move,
	effectMediator,device),
	animTimer(20.0f), anim(animTimer)
{
}

BurnStar::~BurnStar()
{
}

void BurnStar::initialize()
{
	Star::initialize();
	animTimer.initialize();
	animTimer.setStarTimer(20.f);
	anim.addCell("F", 1,2, 64, 64);//ˆÚ“®¶
}
void BurnStar::updata()
{
	Star::updata();
	

	
	anim.updata("F");
	animTimer.updata();
}
void BurnStar::collision(const GameObject* obj)
{
	Star::collision(obj);
}
void BurnStar::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (isInScreen(scroll))
	{
		if (!device.getSound().IsPlaySE("star_fire.wav"))
		{
			device.getSound().PlaySE("star_fire.wav");
		}
	}

	Star::draw(renderer,scroll);
	anim.draw(renderer,"fire.bmp", &scroll.transformViewPosition(position));
}

Star* BurnStar::clone()
{
	return new BurnStar(textrue, startPosi, viewSize, rect, helth, 
		StarMove_Ptr(move->clone()), effectMediator,device);
}
GameObject* BurnStar::clone(const GSvector2& position)
{
	return new BurnStar(textrue, position, viewSize, rect, helth,
		StarMove_Ptr(move->clone()), effectMediator, device);
}