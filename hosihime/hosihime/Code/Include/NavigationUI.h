#ifndef _NAVIGATIONUI_H_
#define _NAVIGATIONUI_H_
#include "GameObje_Include.h"
#include <vector>
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
	void remove();
	void between_Player_Goal(std::vector<GameObj_Ptr>* out);
	//target�̈ʒu�ƃT�C�Y��Ԃ�
	const MyRectangle targetRect(GameObj_Ptr min);
	const GSvector2 viewClmp(const GSvector2& position);
private:
	IMediator& mediator;
	std::vector<GameObj_Ptr>respawns;
	GSvector2 position;
	bool isDraw;
	float angle;
	const Scroll& scroll;

	MyRectangle debrect;
};
#endif
