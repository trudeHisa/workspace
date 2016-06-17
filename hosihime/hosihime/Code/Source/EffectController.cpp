#include"EffectController.h"
#include <algorithm>
EffectController::EffectController(const EffectsFactory& factory)
	:factory(factory)
{
}

EffectController::~EffectController()
{
}

void EffectController::initialize()
{
	effects.clear();
}
void EffectController::update()
{
	for each (Effect_Ptr e in effects)
	{
		e->update();
	}
	remove();
}
void EffectController::draw(const Renderer& renderer, const Scroll& scroll)
{
	for each (Effect_Ptr e in effects)
	{
		e->draw(renderer,scroll);
	}
}
void EffectController::remove()
{
	auto itrNewEnd = std::remove_if(effects.begin(), effects.end(), [](Effect_Ptr p)->bool
	{
		return p->getIsEnd();
	});
	effects.erase(itrNewEnd, effects.end());
}

void EffectController::finish()
{

}
void EffectController::add(const std::string& name, const GSvector2& position)
{
	effects.emplace_back(factory->create(name,position));
	effects.back()->initialize();
}