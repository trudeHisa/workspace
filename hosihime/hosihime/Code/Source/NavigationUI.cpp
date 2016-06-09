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
	respawns.clear();
	mediator.gets(&respawns, RESPAWN);
	goal=mediator.get(GOAL);
}
void NavigationUI::updata()
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();

	auto min = std::min_element(respawns.begin(), respawns.end(), [&](GameObj_Ptr obj1, GameObj_Ptr obj2)->bool
	{
		return  obj1->getPosition().distance(playerPos)<obj2->getPosition().distance(playerPos);
	});
	Calculate<float>calc;
	position = (*min)->getPosition();
	position.x = calc.clamp(position.x,0,WINDOW_WIDTH-viewSize.x);
	position.y = calc.clamp(position.y, 0, WINDOW_HEIGHT- viewSize.y);
	remove();
}
void NavigationUI::remove()
{
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	MyRectangle playerForGoal(playerPos, goal->getPosition());

	auto itrNewEnd = std::remove_if(respawns.begin(), respawns.end(), [&](GameObj_Ptr obj)->bool
	{
		return !obj->getRect().intersects(&playerForGoal);
	});
	respawns.erase(itrNewEnd, respawns.end());
}
void NavigationUI::draw(const Renderer& renderer, const Scroll& scroll)
{
	renderer.DrawTextrue(textrue,&position);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position){
	return new NavigationUI(textrue,mediator);
}