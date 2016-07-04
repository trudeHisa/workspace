#include "Magpie.h"

#include "Calculate.h"
Magpie::Magpie(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, IMediator* objMediator,Device& device)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::MAGPIE),
	objMediator(objMediator), state(STANDBY),// timer(1, 1),
	angle(0), speed(5), anim(animTimer), animTimer(30.0f), device(device)
{
}

Magpie::~Magpie()
{
}

void Magpie::initialize()
{
	GameObject::initialize();
	t = 0;
	animTimer.initialize();
	animTimer.setStarTimer(60.0f);
	anim.addCell("Right", 1, 3, 128, 128);
	anim.addCell("Left", 2, 3, 128, 128);
	dir = "Right";
	anim.updata(dir);
	state=STANDBY;
	angle = 0;
	speed = 5;
}

void Magpie::updata()
{
	Calculate<float> calc;	
	 dir = velocity.x >= 0 ? "Right" : "Left";
	switch (state)
	{
	case Magpie::STANDBY:
		angle += -0.1f;
		angle = calc.wrap(angle, 0, 360);
		velocity.y = std::sin(angle)*0.1f*gsFrameTimerGetTime();
		break;
	case Magpie::TAKEIN:
		//		timer.update();
		t +=t>60?1*gsFrameTimerGetTime():0;
		anim.updata(dir);
		animTimer.updata();
		
		if (t>60)
		{
			return;
		}
		if (position.distance(targetPoint) <=velocity.length()*speed)
		{
			state = SENDON;
			targetPoint = targetPoint + GSvector2(1500,-800);
			float alpha = gsFrameTimerGetTime() * 10 / targetPoint.length();
			velocity = position.lerp(targetPoint, alpha) - position;
			velocity.normalize();
		}
		break;
	case Magpie::SENDON:
		speed = 8;
		break;
	default:
		break;
	}
	position += velocity*gsFrameTimerGetTime()*speed;
	//device.getSound().StopSE("kasasagi_fly.wav");
	/*if (isRide())
	{
		
	}*/
}
void Magpie::collision(const GameObject* obj)
{
	if (obj->getType() != GAMEOBJ_TYPE::PLAYER)
	{
		return;
	}
	if (state == STANDBY)
	{
		state = TAKEIN;
		targetPoint = objMediator->get(GAMEOBJ_TYPE::MAGPIE_ENDSPOT)->getPosition();
		targetPoint.y -= viewSize.y;
		float alpha= gsFrameTimerGetTime() * 30 / targetPoint.length();
		velocity = position.lerp(targetPoint, alpha) - position;
		velocity.normalize();
	}
}

void Magpie::setPlayerPosi(GSvector2* playerPosi)
{
	playerPosi->x = position.x + 32;
	playerPosi->y = position.y + 32;
}

void Magpie::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isInScreen(scroll))
	{
		return;
	}
	anim.draw(renderer,textrue, &scroll.transformViewPosition(position));
}

GameObject* Magpie::clone(const GSvector2& position)
{
	return new Magpie(textrue, position, viewSize, rect,objMediator,device);
}
const bool Magpie::isRide()const
{
	return state == TAKEIN;
}