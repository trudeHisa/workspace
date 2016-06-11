#ifndef _NAVIGATIONUI_H_
#define _NAVIGATIONUI_H_
#include "GameObje_Include.h"
#include <vector>
#include <map>
class IMediator;
class NavigationUI:public GameObject
{
public:
	NavigationUI(const std::string& textrue, IMediator& mediator, const Scroll& scroll);
	~NavigationUI();
	void initialize();
	void updata();
	void draw(const Renderer& renderer, const Scroll& scroll);	
	void collision(const GameObject* obj);
	GameObject* clone(const GSvector2& position) ;
private:
	/*
	*リスポンの中で一番優先度の高い(値が低い)リスポンを返す
	*/
	const GameObj_Ptr priorityHigh_Respawn()const;

	void targetInScreen(const GameObj_Ptr target);

	/*
	*minとゴールと比べて近いほうを返す
	*/
	const GameObj_Ptr nearTarget(const GameObj_Ptr& min)const;
	/*
	*画面内に収まるように
	*/
	const GSvector2 viewClmp(const GSvector2& position)const;

private:
	IMediator& mediator;
	/*
	*オブジェクトをキーとして
	*値を優先順位とする
	*値が近いほど優先度が高い
	*/
	std::map <GameObj_Ptr, int>priority;
	//std::vector<GameObj_Ptr>respawns;
	GSvector2 position;
	bool isDraw;
	float angle;
	const Scroll& scroll;
};
#endif
