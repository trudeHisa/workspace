#ifndef _HIKOBOSHI_H_
#define _HIKOBOSHI_H_
#include <gslib.h>
#include "GameObject.h"

class Hikoboshi : public GameObject
{
private:
	Hikoboshi(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, const MyRectangle& rect);
	virtual ~Hikoboshi();
	void updata();
	void collision(const GameObject* obj);
	GameObject* clone(const GSvector2& position);

public:

};
#endif