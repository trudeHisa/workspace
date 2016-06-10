#include "NavigationUI.h"
#include "IMediator.h"
#include <algorithm>
#include "Calculate.h"
NavigationUI::NavigationUI(const std::string& textrue, IMediator& mediator,const Scroll& scroll)
	:GameObject(textrue, GSvector2(0, 0),
	 GSvector2(64,64), MyRectangle(0, 0, 0, 0), UI),
	 mediator(mediator),scroll(scroll), respawns(),
	 isDraw(true), angle(0), debrect(0,0,0,0)
{
}

NavigationUI::~NavigationUI()
{
}

void NavigationUI::initialize()
{	
	GameObject::initialize();
	respawns.clear();
	mediator.gets(&respawns, RESPAWN);
	isDraw=true;
	angle = 0;
}
void NavigationUI::updata()
{
	/**
	*ゴールとプレイヤーの間にあるリスポーンの割り出しができていない
	*/
	//remove();
	std::vector<GameObj_Ptr>between;
	between.clear();
	between_Player_Goal(&between);
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();

	auto min = std::min_element(between.begin(), between.end(),
		[&](GameObj_Ptr obj1, GameObj_Ptr obj2)
	{
		return  obj1->getPosition().distance(playerPos) < obj2->getPosition().distance(playerPos);
	});
	GameObj_Ptr minptr = 0;
	if (min != between.end())
	{
		minptr = *min;
	}
	MyRectangle target = targetRect(minptr);
	position = target.getPosition();
	GSvector2 targetViewPos = position - scroll.getMovingAmount();
	isDraw = !scroll.isInsideWindow(targetViewPos, target.getSize());
	
	GSvector2 v = playerPos - target.getPosition();
	angle=v.degree(playerPos);
}
void NavigationUI::between_Player_Goal(std::vector<GameObj_Ptr>* out)
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	GSvector2 size = playerPos - mediator.get(GOAL)->getPosition();

	MyRectangle playerForGoal(playerPos, size);
	debrect = playerForGoal;
	for each (GameObj_Ptr obj in respawns)
	{
		MyRectangle rect(obj->getPosition(), obj->getRect().getSize());
		if (rect.intersects(&playerForGoal))
		{
			out->emplace_back(obj);
		}
	}
}
const MyRectangle NavigationUI::targetRect(GameObj_Ptr min)
{
	GameObj_Ptr goal = mediator.get(GOAL);
	GSvector2 targetPos = goal->getPosition();
	GSvector2 targetSize = goal->getRect().getSize();
	textrue = "nav1.bmp";
	if (min !=0)
	{
		targetPos =min->getPosition();
		targetSize =min->getRect().getSize();
		textrue = "nav2.bmp";
	}
	return MyRectangle(targetPos,targetSize);
}
const GSvector2 NavigationUI::viewClmp(const GSvector2& position)
{	
	GSvector2 halfSize = viewSize;
	halfSize /= 2;
	GSvector2 windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Calculate<float>calc;
	return calc.clamp(position,halfSize,windowSize+halfSize);
}
void NavigationUI::remove()
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	GSvector2 size = playerPos- mediator.get(GOAL)->getPosition();
	MyRectangle playerForGoal(playerPos,size);

	auto itrNewEnd = std::remove_if(respawns.begin(), respawns.end(), [&](GameObj_Ptr obj)->bool
	{
		MyRectangle rect(obj->getPosition(),obj->getRect().getSize());
		return !rect.intersects(&playerForGoal);
	});
	respawns.erase(itrNewEnd, respawns.end());
}
void NavigationUI::draw(const Renderer& renderer, const Scroll& scroll)
{
	GSvector2 pos = position - scroll.getMovingAmount();
	if (!isDraw)
	{
		return;
	}
	renderer.DrawString(
		"x:" + std::to_string(debrect.getPosition().x) +
		",y:" +std::to_string(debrect.getPosition().y)
		,&GSvector2(10,10),20);

	renderer.DrawString(
		"w:" + std::to_string(debrect.getSize().x) + 
		",h:" + std::to_string(debrect.getSize().y),
		&GSvector2(10,30), 20);
	GSvector2 center=viewSize;
	center /= 2;	
	renderer.DrawTextrue(textrue, &viewClmp(pos), NULL,&center, NULL, angle, NULL);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position){
	return new NavigationUI(textrue,mediator,scroll);
}