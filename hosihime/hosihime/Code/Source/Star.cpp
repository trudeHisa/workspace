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
	starHelth = helth - std::hypotf(
		fabs(position.x - startPosi.x),
		fabs(position.y - startPosi.y));
	if (starHelth < 0)
	{
		isDead = true;
	}
}
void Star::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isInScreen(scroll))
	{
		return;
	}
	GSvector2 pos = scroll.transformViewPosition(position);
	GSvector2 center(viewSize);
	center /= 2;
	pos += center;

	renderer.AdditionBlend();
	float red, green, blue, alpha;//���̐F�A���ߕϐ�
	//�_�ŏ���
	//�����ړ������̔����i�ނƐF�ς��Ɠ_�ŏ���������
	if (starHelth < helth / 4)
	{
		blinkerTime += gsFrameTimerGetTime();
		red = 1.0f;
		green = 0.0f;
		blue = 0.0f;
	}
	else
	{
		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
	}
	//�_��
	if (blinkerTime > 0.7f)
	{
		starAlpha = !starAlpha;
		blinkerTime = 0.0f;
	}
	if (starAlpha)
	{
		alpha = 0.5f;
	}
	else
	{
		alpha = 1.0f;
	}
	renderer.DrawBlurTextrue(textrue,pos,&center,velocity,angle,7);
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos, NULL, &center, &GSvector2(1, 1), angle, &GScolor(red, green, blue, alpha));
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
		effectMediator->add("FireworkEffect", position + (viewSize*0.5f));
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
IStarMove* Star::getMove()
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