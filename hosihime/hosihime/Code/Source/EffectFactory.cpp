#include "EffectFactory.h"
#include "CircleEffect.h"
#include "StarEffect.h"
#include "LightEffect.h"
#include "FireworkEffect.h"
#include "StarEffect.h"

EffectFactory::EffectFactory()
	:container()
{
}

EffectFactory::~EffectFactory()
{
}
const Effect_Ptr EffectFactory::create(const std::string& key, const GSvector2& position)const
{
	return Effect_Ptr(container.at(key)->clone(position));
}
void EffectFactory::addContainer()
{
	container.insert(std::pair<const std::string, Effect_Ptr >("CircleEffect", Effect_Ptr(new CircleEffect())));
	container.insert(std::pair<const std::string, Effect_Ptr >("StarEffect", Effect_Ptr(new StarEffect())));
	container.insert(std::pair<const std::string, Effect_Ptr >("LightEffect", Effect_Ptr(new LightEffect())));
	container.insert(std::pair<const std::string, Effect_Ptr >("FireworkEffect", Effect_Ptr(new FireworkEffect())));
}