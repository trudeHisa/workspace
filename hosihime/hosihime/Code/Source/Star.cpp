#include "Star.h"
#include "Calculate.h"

Star::Star(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, float helth,
	StarMove_Ptr move, IEffectMediator* effectMediator)
	:GameObject(textrue, position, viewSize, rect, STAR),
	move(move), startPosi(position), angle(0), helth(helth),
	effectMediator(effectMediator)
{
}
Star::~Star()
{
}
void Star::initialize()
{
	velocity = GSvector2(0, 0);
	isDead = false;
	isDraw = true;
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
	if (helth < position.distance(startPosi))
	{
		isDead = true;
	}
	isDraw = true;
}
void Star::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (isDraw == false)
	{
		return;
	}
	if (!isInScreen(scroll))
	{
		return;
	}	
	GSvector2 pos = scroll.transformViewPosition(position);
	GSvector2 center(viewSize);
	center /= 2;
	pos += center;

	renderer.AdditionBlend();
	renderer.DrawBlurTextrue(textrue, pos, &center, velocity, angle, 7);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos, NULL, &center, &GSvector2(1, 1), angle, NULL);
}
void Star::collision(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();
	if (type == STAR ||
		type == BREAKSTAR ||
		type == BURNSTAR ||
		type == PLANET)
	{
		isDead = true;
		effectMediator->add("FireworkEffect",position+(viewSize*0.5f));
	}
	if (type == PLAYER)
	{
		isDraw = false;
	}
	else
	{
		isDraw = true;
	}
}
Star* Star::clone()
{
	return new Star(textrue, startPosi, viewSize, rect, helth, StarMove_Ptr(move->clone()), effectMediator);
}
GameObject* Star::clone(const GSvector2& position)
{
	return new Star(textrue, position, viewSize, rect, helth, StarMove_Ptr(move->clone()), effectMediator);
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
	//velocityの長さで回転速度を決める
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle + add, 0, 360);
}

void Star::nonCollision()
{
	//isDraw = true;
}