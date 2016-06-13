#include "Star.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, float helth, StarMove_Ptr move)
	:GameObject(textrue, position, viewSize, rect,STAR),
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

	//三平方の定理
	/*if (helth - std::hypotf(
		fabs(position.x - startPosi.x),
		fabs(position.y - startPosi.y)) < 0)*/
	if (helth<position.distance(startPosi))
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
		GSvector2 prevpos = position - vel*i*0.8f;
		float prevang = angle - addRot*i;
		float alpha = (max - i)*0.05f;
		renderer.DrawTextrue(textrue, &prevpos, NULL, &center, &GSvector2(1, 1), prevang, &GScolor(1, 1, 1, alpha));
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
	//animation.draw(renderer,textrue,&pos);
	renderer.AdditionBlend();
	blurdraw(renderer,pos,center);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos,NULL,&center,&GSvector2(1,1),angle,NULL);
}
void Star::collision(const GameObject* obj)
{
	if ( obj->getType()==PLANET)
	{
		isDead = true;
	}
}
void Star::ride(GSvector2* position,const GSvector2* size)const
{
	GSvector2 pos(this->position);
	pos.y -=size->y;
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
void Star::rotate()
{
	Calculate<float>calc;
	//velocityの長さで回転速度を決める
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle +add, 0, 360);
}