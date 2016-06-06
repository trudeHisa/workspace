#ifndef _IMMOVABLE_H_
#define _IMMOVABLE_H_
#include "GameObject.h"
class ImMovable: public GameObject
{
public:
	ImMovable(const std::string& textrue,const GSvector2& position ,
		const GSvector2& viewSize,const MyRectangle& rect, GAMEOBJ_TYPE type);
	virtual ~ImMovable();
	void updata();
	void collision(const GameObject* obj);
	GameObject* clone(const GSvector2& position);
};
#endif