#include "EffectFactory.h"
#include "CircleEffect.h"
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
}