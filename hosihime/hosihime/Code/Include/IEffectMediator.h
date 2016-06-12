#ifndef _IEFFECTMEDIATOR_H_
#define _IEFFECTMEDIATOR_H_

#include <string>
#include <GSvector2.h>

class IEffectMediator
{
public:
	virtual ~IEffectMediator(){}
	/*
	*���O�ōH�ꂩ��Efect���w��̈ʒu�ɐ���
	*/
	virtual void add(const std::string& name,const GSvector2& position) = 0;
};
#endif