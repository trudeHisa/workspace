#ifndef _IMMOVABLE_H_
#define _IMMOVABLE_H_
#include "GameObject.h"
class ImMovable: public GameObject
{
public:
	ImMovable(const std::string& textrue, const MyRectangle& rect,GAMEOBJ_TYPE type);
	~ImMovable();
	void updata();
	void collision(const GameObject* obj);
private:

};
#endif