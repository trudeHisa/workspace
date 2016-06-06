#include "Star.h"
#include "IStarMove.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const MyRectangle& rect,IStarMove* move)
	:GameObject(textrue, rect, STAR), 
	move(move), 
	startPosi(rect.getPosition()),
	angle(0)
{
}
Star::~Star()
{
	delete move;
	move = NULL;
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
	rect.translate(velocity*gsFrameTimerGetTime());
	if (rect.getPosition().y >WINDOW_HEIGHT + rect.getHeight() * 2
		|| rect.getPosition().y< - rect.getHeight() * 2)
	{
		isDead = true;
	}
}
void Star::draw(Renderer& renderer, const Scroll* scroll)
{
	GSvector2 pos = rect.getPosition();
	pos -= scroll->getMovingAmount();
	if (!scroll->isInsideWindow(pos, rect.getSize()))
	{
		return;
	}
	GSvector2 center(rect.getSize());
	center /= 2;
	pos += center;
	//renderer.AdditionBlend();
	renderer.DrawTextrue(textrue, &pos,NULL,&center,&GSvector2(1,1),angle,NULL);
	//renderer.InitBlendFunc();
}
void Star::collision(const GameObject* obj)
{
	if ( obj->isSameType(PLANET))
	{
		isDead = true;
	}
}
void Star::ride(MyRectangle* rect)
{
	GSvector2 pos(this->rect.getPosition());
	pos.y -= rect->getHeight();
	rect->resetPosition(pos);
}
void Star::pickUp(GSvector2* velocity)
{
	*velocity = this->velocity;
}
Star* Star::clone()
{
	return new Star(textrue, MyRectangle(startPosi,rect.getSize()), move->clone());
}

const GSvector2& Star::getSPosi() const
{
	return startPosi;
}

void Star::rotate()
{
	Calculate<float>calc;
	//velocity‚Ì’·‚³‚Å‰ñ“]‘¬“x‚ðŒˆ‚ß‚é
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle +add, 0, 360);
}