#ifndef _NAVIGATIONUI_H_
#define _NAVIGATIONUI_H_
#include "GameObje_Include.h"
#include <vector>
class IMediator;
class NavigationUI:public GameObject
{
public:
	NavigationUI(const std::string& textrue,IMediator& mediator);
	~NavigationUI();
	void initialize();
	void updata();
	void draw(const Renderer& renderer, const Scroll& scroll);	
	void collision(const GameObject* obj);
	GameObject* clone(const GSvector2& position) ;
private:
	void remove();
	void viewClmp(const GSvector2& position);
private:
	IMediator& mediator;
	std::vector<GameObj_Ptr>respawns;
	//GameObj_Ptr goal;
	GSvector2 position;


	GSvector2 debPos;

};
#endif
