#ifndef _IEFFECTMEDIATOR_H_
#define _IEFFECTMEDIATOR_H_

#include <string>
#include <GSvector2.h>

class IEffectMediator
{
public:
	virtual ~IEffectMediator(){}
	/*
	*名前で工場からEfectを指定の位置に生成
	*/
	virtual void add(const std::string& name,const GSvector2& position) = 0;
};
#endif