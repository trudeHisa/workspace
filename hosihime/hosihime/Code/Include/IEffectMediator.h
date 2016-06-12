#ifndef _IEFFECTMEDIATOR_H_
#define _IEFFECTMEDIATOR_H_

#include <string>
#include <GSvector2.h>

class IEffectMediator
{
public:
	virtual ~IEffectMediator(){}
	/*
	*–¼‘O‚ÅHê‚©‚çEfect‚ğw’è‚ÌˆÊ’u‚É¶¬
	*/
	virtual void add(const std::string& name,const GSvector2& position) = 0;
};
#endif