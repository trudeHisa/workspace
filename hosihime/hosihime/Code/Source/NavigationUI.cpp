#include "NavigationUI.h"
#include "IMediator.h"
#include <algorithm>
#include "Calculate.h"
NavigationUI::NavigationUI(const std::string& textrue, IMediator& mediator, const Scroll& scroll)
	:GameObject(textrue, GSvector2(0, 0),
	GSvector2(64, 64), MyRectangle(0, 0, 0, 0), UI),
	mediator(mediator), scroll(scroll), priority(),
	isDraw(true), angle(0)
{
}

NavigationUI::~NavigationUI()
{
}

void NavigationUI::initialize()
{
	GameObject::initialize();
	priority.clear();

	//���X�|�����Q�b�g
	std::vector<GameObj_Ptr>respawns;
	mediator.gets(&respawns, RESPAWN);

	/**
	*�X�^�[�g�n�_�Ƃ̋����Ń\�[�g
	*�߂���
	*/
	GSvector2 startPos = mediator.get(START)->getPosition();

	std::sort(respawns.begin(), respawns.end(),
		[&](GameObj_Ptr obj1, GameObj_Ptr obj2)
	{
		return  obj1->getPosition().distance(startPos) < obj2->getPosition().distance(startPos);
	});

	//�߂����X�|�����珇�ɗD��xi�œo�^
	for (unsigned int i = 0; i < respawns.size(); i++)
	{
		priority.insert(std::pair<GameObj_Ptr, int>(respawns[i], i));
	}

	isDraw = true;
	angle = 0;
}
void NavigationUI::updata()
{
	GameObj_Ptr target = nearTarget(priorityHigh_Respawn());

	targetInScreen(target);
	GSvector2 targetCenterPos = target->getPosition() + (target->getViewSize()*0.5f);
	GSvector2 targetViewPos =scroll.transformViewPosition(targetCenterPos);

	/*
	target�̈ʒu����ʓ��ɃN�����v����
	�`��ʒu�Ɉʒu����
	*/
	position = viewClmp(targetViewPos);

	/*
	*��]�p�x
	*/
	GSvector2 v =targetViewPos- (position + (viewSize*0.5f));
	Calculate<float>calc;
	angle = calc.radToDeg(std::atan2(v.y, v.x));


	if (target->getType() == RESPAWN)
	{
		textrue = "nav2.bmp";
		return;
	}
	textrue = "nav1.bmp";
}
const GameObj_Ptr NavigationUI::priorityHigh_Respawn()const
{
	auto min = std::min_element(priority.begin(), priority.end(),
		[](std::pair<GameObj_Ptr, int> value1, std::pair<GameObj_Ptr, int> value2)
	{
		return  value1.second < value2.second;
	});
	return min->first;
}

void NavigationUI::targetInScreen(const GameObj_Ptr target)
{
	if (!target->isInScreen(scroll))
	{
		//��ʊO
		isDraw = true;
		return;
	}
	//��ʓ�
	isDraw = false;
	if (target->getType() != RESPAWN)
	{
		return;
	}
	/**
	*�^�[�Q�b�g�����X�|���Ȃ�D��x��������
	*(�l���グ��)
	*/
	priority.at(target) += priority.size();
}

const GameObj_Ptr NavigationUI::nearTarget(const GameObj_Ptr& min)const
{
	const GameObj_Ptr& goal = mediator.get(GOAL);
	GSvector2 goalPos = goal->getPosition();

	GSvector2 playerPos = mediator.get(PLAYER)->getPosition();
	if (goalPos.distance(playerPos) < min->getPosition().distance(playerPos))
	{
		return goal;
	}
	return min;
}

const GSvector2 NavigationUI::viewClmp(const GSvector2& position)const
{
	GSvector2 halfSize = viewSize;
	halfSize /= 2;
	GSvector2 windowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Calculate<float>calc;
	return calc.clamp(position, halfSize, windowSize - halfSize);
}

void NavigationUI::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isDraw)
	{
		return;
	}
	GSvector2 center = viewSize;
	center /= 2;
	renderer.DrawTextrue(textrue, &position, NULL, &center, NULL, angle, NULL);
}
void NavigationUI::collision(const GameObject* obj){}
GameObject* NavigationUI::clone(const GSvector2& position)
{
	return new NavigationUI(textrue, mediator, scroll);
}