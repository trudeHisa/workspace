#include "Star.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize,const MyRectangle& rect,StarMove_Ptr move,float helth)
	:GameObject(textrue, position, viewSize, rect,STAR),
	move(move), startPosi(position), angle(0), helth(helth)
	//,animTimer(6),animation(animTimer),activeAnimKey(1)//5,4:64:64
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
	//animTimer.initialize();
	//for (int i = 1; i <5; i++)
	//{
	//	animation.addCell(std::to_string(i),i, 5, viewSize.x, viewSize.y);
	//}	
	//activeAnimKey = 1;
}
void Star::updata()
{
	//animTimer.updata();
	//if (animTimer.isZero())
	//{
	//	Calculate<int>calc;
	//	activeAnimKey=calc.wrap(activeAnimKey+1,1, 4);
	//}
	//animation.updata(std::to_string(activeAnimKey));

	velocity = move->moving();
	rotate();

	position += velocity*gsFrameTimerGetTime();

	//O•½•û‚Ì’è—
	if (helth - std::hypotf(
		fabs(position.x - startPosi.x),
		fabs(position.y - startPosi.y)) < 0)
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
	GSvector2 pos = position;
	pos -= scroll.getMovingAmount();
	if (!scroll.isInsideWindow(pos, viewSize))
	{
		return;
	}
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
	return new Star(textrue, startPosi, viewSize, rect, StarMove_Ptr(move->clone()),helth);
}
GameObject* Star::clone(const GSvector2& position)
{
	return new Star(textrue, position, viewSize, rect, StarMove_Ptr(move->clone()),helth);
}
const GSvector2& Star::getSPosi() const
{
	return startPosi;
}
void Star::rotate()
{
	Calculate<float>calc;
	//velocity‚Ì’·‚³‚Å‰ñ“]‘¬“x‚ğŒˆ‚ß‚é
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle +add, 0, 360);
}