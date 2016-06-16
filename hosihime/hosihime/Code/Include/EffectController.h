#ifndef _EFFECTCONTROLLER_H_
#define _EFFECTCONTROLLER_H_

#include <vector>
#include "IEffectMediator.h"
#include "IEffect.h"
#include "Factory.h"

/*
*Effect���Ǘ�����N���X
*
*Effect�֌W�ōő�N���X
*add��Factory����Clone���󂯎��
*
*
*/

typedef std::shared_ptr<IEffect>Effect_Ptr;
typedef std::shared_ptr<Factory<Effect_Ptr, const std::string&>> EffectsFactory;
class EffectController:public IEffectMediator
{
public:
	EffectController(const EffectsFactory& factory);
	~EffectController();
	void initialize();
	void update();
	void draw(const Renderer& renderer, const Scroll& scroll);
	void finish();
	void add(const std::string& name, const GSvector2& position);
private:
	void remove();
private:
	std::vector<Effect_Ptr>effects;
	EffectsFactory factory;
};
#endif
