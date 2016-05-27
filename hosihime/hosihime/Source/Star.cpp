#include "Star.h"
#define PAI 3.14f
Star::Star(const std::string& textrue, const GSvector2& position,IStarMove* move)
	:GameObject(textrue, MyRectangle(position, position + GSvector2(64, 64)), STAR), 
	move(move), startPosi(position)
{
}


Star::~Star()
{
	delete move;
	move = NULL;
}
void Star::finish()
{
}

void Star::initialize()
{
	velocity = GSvector2(0, 0);
	isDead = false;
	ang = 0;
}

void Star::updata()
{
	velocity = move->moving();
	//velocity = GSvector2(3,0);
	//*gsFrameTimerGetTime()
	rect.translate(velocity);
	if (WINDOW_HEIGHT+rect.getHeight() < rect.getMin().y)
	{
		isDead = true;
	}
}
void Star::collision(const GameObject* obj)
{
	if (obj->isSameType(ROCK) || obj->isSameType(PLANET))
	{
		isDead = true;
	}

}
void Star::pickUp(GSvector2* vel)
{
	vel->x = velocity.x;
	vel->y = velocity.y;
}
void Star::ride(MyRectangle* rect)
{
	GSvector2 vel(0,0);
	vel.x = this->rect.getMin().x- rect->getMin().x;
	vel.y = (this->rect.getMin().y - rect->getHeight())- rect->getMin().y;
	rect->translate(vel);
}

Star* Star::clone()
{
	return new Star(textrue, startPosi);
}