#include "Star.h"
#include "Calculate.h"

//star_yellow.bmp
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
	starHelth = helth;//helthを代入
	blinkerTime = 0;//星の点滅用変数
	starAlpha = false;//星の透過判定

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

	//三平方の定理
	starHelth = helth - std::hypotf(
		fabs(position.x - startPosi.x),
		fabs(position.y - startPosi.y));
	if (starHelth < 0)
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
	float red, green, blue,alpha;//星の色、透過変数
	//点滅処理
	//星が移動距離の半分進むと色変えと点滅処理をする
	if (starHelth < helth / 2)
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
		blurdraw(renderer, pos, center);
	}
	//点滅
	if(blinkerTime > 0.7f)
	{
		starAlpha = !starAlpha;
		blinkerTime = 0.0f;
	}
	if(starAlpha)
	{
		alpha = 0.5f;
	}
	else
	{
		alpha = 1.0f;
	}
	renderer.InitBlendFunc();
	renderer.DrawTextrue(textrue, &pos,NULL,&center,&GSvector2(1,1),angle,&GScolor(red,green,blue,alpha));
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
	//velocityの長さで回転速度を決める
	float add = gsFrameTimerGetTime()*velocity.length();
	angle = calc.wrap(angle +add, 0, 360);
}