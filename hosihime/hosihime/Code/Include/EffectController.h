#ifndef _EFFECTCONTROLLER_H_
#define _EFFECTCONTROLLER_H_

#include <vector>
#include "IEffectMediator.h"
#include "IEffect.h"
#include "EffectFactory.h"
typedef std::shared_ptr<IEffect>Effect_Ptr;
class EffectController:public IEffectMediator
{
public:
	EffectController(const EffectFactory& factory);
	~EffectController();
	void initialize();
	void updata();
	void draw(const Renderer& renderer);
	void finish();
	void add(const std::string& name, const GSvector2& position);
private:
	void remove();
private:
	std::vector<Effect_Ptr>effects;
	const EffectFactory& factory;
};
#endif
