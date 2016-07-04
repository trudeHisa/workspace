#include "Star.h"
#include "Calculate.h"

#define COLOR_RED GScolor(1,0,0,1)
#define COLOR_WHITE GScolor(1,1,1,1)
Star::Star(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, const MyRectangle& rect, float helth,
	StarMove_Ptr move, IEffectMediator* effectMediator,
	Device& device)
	:GameObject(textrue, position, viewSize, rect, GAMEOBJ_TYPE::STAR),
	move(move), startPosi(position), angle(0), helth(helth),
	effectMediator(effectMediator), device(device)
{
}
Star::~Star()
{
}
void Star::initialize()
{
	velocity = GSvector2(0, 0);
	isDead = false;
	//isDraw = true;
	angle = 0;
	starHelth = helth;//helth����
	blinkerTime = 0;//���̓_�ŗp�ϐ�
	starAlpha = false;//���̓��ߔ���

	//animTimer.initialize();
	//for (int i = 1; i <5; i++)
	//{
	//	animation.addCell(std::to_string(i),i, 5, viewSize.x, viewSize.y);
	//}	
	//activeAnimKey = 1;
}
void Star::updata()
{
	velocity = move->moving();
	rotate();

	position += velocity*gsFrameTimerGetTime();

	//�O�����̒藝
	starHelth -= velocity.length()*gsFrameTimerGetTime();
	if (starHelth < 0)
	{
		isDead = true;
	}
	//isDraw = true;
}
void Star::draw(const Renderer& renderer, const Scroll& scroll)
{
	/*if (isDraw == false)
	{
		return;
	}*/
	if (!isInScreen(scroll))
	{
		return;
	}	
	GSvector2 pos = scroll.transformViewPosition(position);
	GSvector2 center(viewSize);
	center /= 2;
	pos += center;

	renderer.AdditionBlend();
	GScolor color;
	//�_�ŏ���
	//�����ړ������̔����i�ނƐF�ς��Ɠ_�ŏ���������
	if (starHelth < helth / 4)
	{
		blinkerTime += gsFrameTimerGetTime();
		color = COLOR_RED;
	}
	else
	{
		color = COLOR_WHITE;
	}
	//�_��
	if (blinkerTime > 0.7f)
	{
		starAlpha = !starAlpha;
		blinkerTime = 0.0f;
	}
	color.w = starAlpha ? 0.5f : 1.0f;


	renderer.DrawBlurTextrue(textrue, pos, &center, velocity, angle, 7);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos, NULL, &center, &GSvector2(1, 1), angle, &color);
}
void Star::collision(const GameObject* obj)
{
	GAMEOBJ_TYPE type = obj->getType();

	if (type == GAMEOBJ_TYPE::PLANET)
	{
		isDead = true;
		effectMediator->add("FireworkEffect", position + (viewSize*0.5f));
		device.getSound().PlaySE("star_break.wav");
	}
	/*if (type == PLAYER)
	{
		isDraw = false;
	}
	else
	{
		isDraw = true;
	}*/
}
Star* Star::clone()
{
	return new Star(textrue, startPosi, viewSize, rect, helth,
		StarMove_Ptr(move->clone()), effectMediator, device);
}
GameObject* Star::clone(const GSvector2& position)
{
	return new Star(textrue, position, viewSize, rect, helth, 
		StarMove_Ptr(move->clone()), effectMediator, device);
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
	//velocity�̒����ŉ�]���x�����߂�
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle + add, 0, 360);
}

void Star::nonCollision()
{
	//isDraw = true;
}