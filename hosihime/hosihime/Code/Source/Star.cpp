#include "Star.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, float helth, StarMove_Ptr move)
	:GameObject(textrue, position, viewSize, rect, STAR),
	move(move), startPosi(position), angle(0), helth(helth)
{
}
Star::~Star()
{
}
void Star::initialize()
{
	velocity = GSvector2(0, 0);
	isDead = false;
	angle = 0;
}
void Star::updata()
{
	velocity = move->moving();
	rotate();

	position += velocity*gsFrameTimerGetTime();

	//O•½•û‚Ì’è—
	/*if (helth - std::hypotf(
		fabs(position.x - startPosi.x),
		fabs(position.y - startPosi.y)) < 0)*/
	if (helth<position.distance(startPosi))
	{
		isDead = true;
	}
}

void Star::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isInScreen(scroll))
	{
		return;
	}
	GSvector2 pos = position - scroll.getMovingAmount();
	GSvector2 center(viewSize);
	center /= 2;
	pos += center;

	renderer.AdditionBlend();
	renderer.DrawBlurTextrue(textrue,pos,&center,velocity,angle,7);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos, NULL, &center, &GSvector2(1, 1), angle, NULL);
}
void Star::collision(const GameObject* obj)
{
	if (obj->getType() == PLANET)
	{
		isDead = true;
	}
}
void Star::ride(GSvector2* position, const GSvector2* size)const
{
	GSvector2 pos(this->position);
	pos.y -= size->y;
	*position = pos;
}
void Star::pickUp(GSvector2* velocity)const
{
	*velocity = this->velocity;
}
Star* Star::clone()
{
	return new Star(textrue, startPosi, viewSize, rect, helth, StarMove_Ptr(move->clone()));
}
GameObject* Star::clone(const GSvector2& position)
{
	return new Star(textrue, position, viewSize, rect, helth, StarMove_Ptr(move->clone()));
}
const GSvector2& Star::getSPosi() const
{
	return startPosi;
}
const float Star::getHelth()const
{
	return helth;
}

const IStarMove* Star::getMove()
{
	return move.get();
}
void Star::rotate()
{
	Calculate<float>calc;
	//velocity‚Ì’·‚³‚Å‰ñ“]‘¬“x‚ğŒˆ‚ß‚é
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle + add, 0, 360);
}