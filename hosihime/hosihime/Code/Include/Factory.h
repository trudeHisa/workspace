#ifndef _FACTORY_H_
#define _FACTORY_H_
#include <GSvector2.h>

template<class T,class K>
/*
* <T,K>
* ’l‚ÆKey
*/
class Factory
{
public:
	virtual ~Factory(){}
	virtual const T create(K key, const GSvector2& position)const = 0;
	virtual void addContainer() = 0;
};
#endif