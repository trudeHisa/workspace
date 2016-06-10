#include "NavigationUI.h"
#include "IMediator.h"
#include <algorithm>
#include "Calculate.h"
NavigationUI::NavigationUI(const std::string& textrue, IMediator& mediator)
	:GameObject(textrue, GSvector2(0, 0),
	 GSvector2(64,64), MyRectangle(0, 0, 0, 0), UI),
	 mediator(mediator), respawns(), goal(0)
{
}

NavigationUI::~NavigationUI()
{
}

void NavigationUI::initialize()
{	
	GameObject::initialize();
	isDraw = true;
	respawns.clear();
	mediator.gets(&respawns, RESPAWN);
	goal=mediator.get(GOAL);
}
void NavigationUI::updata()
{
	remove();
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	auto min = std::min_element(respawns.begin(), respawns.end(),
		[&](GameObj_Ptr obj1, GameObj_Ptr obj2)
	{
		return  obj1->getPosition().distance(playerPos)<obj2->getPosition().distance(playerPos);
	});
	GSvector2 pos = goal->getPosition();
	if (min != respawns.end())
	{
		pos = (*min)->getPosition();
	}
	isDraw = isPositionInScreen(pos);
	viewClmp(pos);
}

bool NavigationUI::isPositionInScreen(const GSvector2& pos)
{
	MyRectangle _rect(pos.x, pos.y, viewSize.x, viewSize.y);
	MyRectangle win(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	return _rect.intersects(&win);
}

void NavigationUI::viewClmp(const GSvector2& position)
{
	this->position = position;
	Calculate<float>calc;
	this->position.x = calc.clamp(position.x, 0, WINDOW_WIDTH - viewSize.x);
	this->position.y = calc.clamp(position.y, 0, WINDOW_HEIGHT - viewSize.y);
}
void NavigationUI::remove()
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	GSvector2 size = goal->getPosition() - playerPos;
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
	if (!isDraw)
	{
		return;
	}
	renderer.DrawTextrue(textrue,&position);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position){
	return new NavigationUI(textrue,mediator);
}