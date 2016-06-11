#include "NavigationUI.h"
#include "IMediator.h"
#include <algorithm>
#include "Calculate.h"
NavigationUI::NavigationUI(const std::string& textrue, IMediator& mediator, const Scroll& scroll)
	:GameObject(textrue, GSvector2(0, 0),
	GSvector2(64, 64), MyRectangle(0, 0, 0, 0), UI),
	mediator(mediator), scroll(scroll), respawns(),
	isDraw(true), angle(0), debrect(0, 0, 0, 0)
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
	isDraw = true;
	angle = 0;
}
void NavigationUI::updata()
{
	/**
	*ゴールとプレイヤーの間にあるリスポーンの割り出しができていない
	*/
	/*std::vector<GameObj_Ptr>between;
	between.clear();
	between_Player_Goal(&between);*/

	/*
	*プレイヤーと一番近いリスポーンの特定
	*/
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	auto min = std::min_element(respawns.begin(),respawns.end(), //between.begin(), between.end(),
		[&](GameObj_Ptr obj1, GameObj_Ptr obj2)
	{
		return  obj1->getPosition().distance(playerPos) < obj2->getPosition().distance(playerPos);
	});
	GameObj_Ptr minptr = 0;
	if (min !=respawns.end()) // between.end())
	{
		minptr = *min;
	}

	MyRectangle target = targetRect(minptr);

	/*
	*targetをview座標に変換
	*targetが画面に映っていたらナビを表示しない
	*/
	position = target.getPosition();
	GSvector2 targetViewPos = position - scroll.getMovingAmount();
//	isDraw = !scroll.isInsideWindow(targetViewPos, target.getSize());

	/*
	*回転角度
	*/
	GSvector2 pos = position - scroll.getMovingAmount();
	GSvector2 v =pos - target.getPosition();
	angle = v.degree(pos);
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
	MyRectangle target(goal->getPosition(), goal->getRect().getSize());
	textrue = "nav1.bmp";
	if (min == 0)
	{
		return target;
	}
	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	if (target.getPosition().distance(playerPos) < min->getPosition().distance(playerPos))
	{
		return target;
	}
	textrue = "nav2.bmp";
	return MyRectangle(min->getPosition(), min->getRect().getSize());
}
const GSvector2 NavigationUI::viewClmp(const GSvector2& position)
{
	GSvector2 halfSize = viewSize;
	//halfSize /= 2;
	GSvector2 windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Calculate<float>calc;
	return calc.clamp(position, halfSize, windowSize - halfSize);
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
		",y:" + std::to_string(debrect.getPosition().y)
		, &GSvector2(10, 10), 20);

	renderer.DrawString(
		"w:" + std::to_string(debrect.getSize().x) +
		",h:" + std::to_string(debrect.getSize().y),
		&GSvector2(10, 30), 20);
	GSvector2 center = viewSize;
	//center /= 2;

	renderer.DrawTextrue(textrue, &viewClmp(pos), NULL, &center, NULL, angle, NULL);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position){
	return new NavigationUI(textrue, mediator, scroll);
}