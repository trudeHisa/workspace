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
	rect.translate(velocity*gsFrameTimerGetTime());
	if (rect.getPosition().y >WINDOW_HEIGHT + rect.getHeight() * 2
		|| rect.getPosition().y< - rect.getHeight() * 2)
	{
		isDead = true;
	}
}
void Star::collision(const GameObject* obj)
{
	if (obj->isSameType(RESPAWN) || obj->isSameType(PLANET))
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

Star* Star::clone()
{
	return new Star(textrue, MyRectangle(startPosi,rect.getSize()), move->clone());
}