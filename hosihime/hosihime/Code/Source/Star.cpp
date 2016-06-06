#include "Star.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const GSvector2& position, const MyRectangle& rect, StarMode_Ptr move)
	:GameObject(textrue,position,rect, STAR), 
	move(move), 
	startPosi(position),
	angle(0)
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
	if (position.y >WINDOW_HEIGHT + rect.getHeight() * 2
		|| position.y< -rect.getHeight() * 2)
	{
		isDead = true;
	}
}
void Star::blurdraw(const Renderer& renderer, const GSvector2& position, const GSvector2& center)
{
	GSvector2 vel = velocity;
	float addRot = gsFrameTimerGetTime()*velocity.length();
	int max =7;
	for (int i = max; i>0; i--)
	{
		GSvector2 fp = position - vel*i*0.8f;
		float fang = angle - addRot*i;
		float alpha = (max - i)*0.05f;
		renderer.DrawTextrue(textrue, &fp, NULL, &center, &GSvector2(1, 1), angle, &GScolor(1, 1, 1, alpha));
	}
}
void Star::draw(const Renderer& renderer, const Scroll& scroll)
{
	GSvector2 pos = position;
	pos -= scroll.getMovingAmount();
	if (!scroll.isInsideWindow(pos, rect.getSize()))
	{
		return;
	}
	GSvector2 center(rect.getSize());
	center /= 2;
	pos += center;
	renderer.AdditionBlend();
	blurdraw(renderer,pos,center);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos,NULL,&center,&GSvector2(1,1),angle,NULL);
}
void Star::collision(const GameObject* obj)
{
	if ( obj->isSameType(PLANET))
	{
		isDead = true;
	}
}
void Star::ride(GSvector2* position,const GSvector2* size)
{
	GSvector2 pos(this->position);
	pos.y -=size->y;
	*position = pos;
}
void Star::pickUp(GSvector2* velocity)
{
	*velocity = this->velocity;
}
Star* Star::clone()
{
	return new Star(textrue, startPosi, MyRectangle(GSvector2(0, 0), rect.getSize()), StarMode_Ptr(move->clone()));
}
GameObject* Star::clone(const GSvector2& position)
{
	return new Star(textrue, position, MyRectangle(GSvector2(0, 0), rect.getSize()), StarMode_Ptr(move->clone()));
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