#include "NavigationUI.h"
#include "IMediator.h"
#include <algorithm>
#include "Calculate.h"
NavigationUI::NavigationUI(const std::string& textrue, IMediator& mediator)
	:GameObject(textrue, GSvector2(0, 0),
	 GSvector2(64,64), MyRectangle(0, 0, 0, 0), UI),
	 mediator(mediator), respawns(), debPos(0,0)//, goal(0
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
	
}
void NavigationUI::updata()
{
	//remove();
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	auto min = std::min_element(respawns.begin(), respawns.end(),
		[&](GameObj_Ptr obj1, GameObj_Ptr obj2)
	{
		return  obj1->getPosition().distance(playerPos) < obj2->getPosition().distance(playerPos);
	});
	GSvector2 pos = mediator.get(GOAL)->getPosition();
	if (min != respawns.end())
	{
		pos = (*min)->getPosition();
	}
	debPos = pos;
	position = pos;
	//viewClmp(pos);
}
void NavigationUI::viewClmp(const GSvector2& position)
{
	Calculate<float>calc;
	this->position.x = calc.clamp(position.x, 0, WINDOW_WIDTH - viewSize.x);
	this->position.y = calc.clamp(position.y, 0, WINDOW_HEIGHT - viewSize.y);
}
void NavigationUI::remove()
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	GSvector2 size = mediator.get(GOAL)->getPosition() - playerPos;
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
	
	for (int i = 0; i <respawns.size(); i++)
	{
		renderer.DrawString("X:" + std::to_string(respawns[i]->getPosition().x) + ",Y:" + std::to_string(respawns[i]->getPosition().y), &GSvector2(100, i * 30), 20);
	}
	renderer.DrawString("X:" + std::to_string(debPos.x) + ",Y:" + std::to_string(debPos.y), &GSvector2(300, 100), 20);
	
	GSvector2 pos = position - scroll.getMovingAmount();
	
	Calculate<float>calc;
	pos.x = calc.clamp(pos.x, 0, WINDOW_WIDTH - viewSize.x);
	pos.y = calc.clamp(pos.y, 0, WINDOW_HEIGHT - viewSize.y);

	renderer.DrawTextrue(textrue, &pos);

	renderer.DrawString("X:" + std::to_string(position.x) + ",Y:" + std::to_string(position.y), &position, 20);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position){
	return new NavigationUI(textrue,mediator);
}