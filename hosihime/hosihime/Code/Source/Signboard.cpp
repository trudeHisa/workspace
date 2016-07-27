#include "Signboard.h"

Signboard::Signboard(const std::string& textrue, const GSvector2& position,
	const GSvector2& viewSize, GAMEOBJ_TYPE type)
	:GameObject(textrue, position, viewSize,MyRectangle(0,0,0,0), type), angle(0)
{
	switch (type)
	{
	case GAMEOBJ_TYPE::SIGNBOARD_R:
		angle = 0;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_L:
		angle = 180;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_U:
		angle = 270;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_D:
		angle = 90;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_RU:
		angle = 315;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_RD:
		angle = 45;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_LU:
		angle =215;
		break;
	case GAMEOBJ_TYPE::SIGNBOARD_LD:
		angle = 135;
		break;
	}
}

Signboard::~Signboard()
{
}

void Signboard::updata()
{
}
void Signboard::collision(const GameObject* obj)
{

}

void Signboard::draw(const Renderer& renderer, const Scroll& scroll)
{
	if (!isInScreen(scroll))
	{
		return;
	}
	GSvector2 center(viewSize);
	center /= 2;
	renderer.drawTextrue(textrue, &scroll.transformViewPosition(position), 
		NULL, &center,NULL, angle, NULL);
}

GameObject* Signboard::clone(const GSvector2& position)
{
	return new Signboard(textrue,position,viewSize,type);
}
