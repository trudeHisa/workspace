#include "Star.h"
#include "IStarMove.h"
#define PAI 3.14f
Star::Star(const std::string& textrue, const MyRectangle& rect,IStarMove* move)
	:GameObject(textrue, rect, STAR), 
	move(move), startPosi(rect.getPosition())
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
	//*gsFrameTimerGetTime()
	rect.translate(velocity);
	if (rect.getPosition().y >WINDOW_HEIGHT + rect.getHeight() * 2
		|| rect.getPosition().y< - rect.getHeight() * 2)
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
	vel.x = this->rect.getPosition().x - rect->getPosition().x;
	vel.y = (this->rect.getPosition().y - rect->getHeight()) - rect->getPosition().y;
	rect->translate(vel);
}

Star* Star::clone()
{
	return new Star(textrue, MyRectangle(startPosi,rect.getSize()), move->clone());
}