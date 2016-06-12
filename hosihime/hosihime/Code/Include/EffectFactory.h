#ifndef _EFFECTFACTORY_H_
#define _EFFECTFACTORY_H_

#include <string>
#include <map>

#include "Factory.h"
#include "IEffect.h"
typedef std::shared_ptr<IEffect>Effect_Ptr;
class EffectFactory :public Factory<Effect_Ptr, const std::string&>
{
public:
	EffectFactory();
	~EffectFactory();
	const Effect_Ptr create(const std::string& key, const GSvector2& position)const;
	void addContainer();
private:
	std::map<const std::string,Effect_Ptr>container;
};
#endif
