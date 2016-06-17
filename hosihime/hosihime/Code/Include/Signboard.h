#ifndef _SIGNBORD_H_
#define _SIGNBORD_H_
#include "GameObject.h"
class Signboard : public GameObject
{
public:
	Signboard(const std::string& textrue, const GSvector2& position,
		const GSvector2& viewSize, GAMEOBJ_TYPE type);
	~Signboard();
	void updata();
	void collision(const GameObject* obj);
	void draw(const Renderer& renderer, const Scroll& scroll);
	GameObject* clone(const GSvector2& position);
private:
	float angle;
};
#endif
