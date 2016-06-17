#include "EffectFactory.h"
#include "CircleEffect.h"
#include "LightEffect.h"
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
	container.insert(std::pair<const std::string, Effect_Ptr >("LightEffect", Effect_Ptr(new LightEffect())));
}