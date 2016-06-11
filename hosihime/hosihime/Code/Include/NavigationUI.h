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
	*���X�|���̒��ň�ԗD��x�̍���(�l���Ⴂ)���X�|����Ԃ�
	*/
	const GameObj_Ptr priorityHigh_Respawn()const;

	void targetInScreen(const GameObj_Ptr target);

	/*
	*min�ƃS�[���Ɣ�ׂċ߂��ق���Ԃ�
	*/
	const GameObj_Ptr nearTarget(const GameObj_Ptr& min)const;
	/*
	*��ʓ��Ɏ��܂�悤��
	*/
	const GSvector2 viewClmp(const GSvector2& position)const;

private:
	IMediator& mediator;
	/*
	*�I�u�W�F�N�g���L�[�Ƃ���
	*�l��D�揇�ʂƂ���
	*�l���߂��قǗD��x������
	*/
	std::map <GameObj_Ptr, int>priority;
	//std::vector<GameObj_Ptr>respawns;
	GSvector2 position;
	bool isDraw;
	float angle;
	const Scroll& scroll;
};
#endif
