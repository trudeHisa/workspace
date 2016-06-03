#ifndef _STARMEDIATOR_H_
#define _STARMEDIATOR_H_
class Star;

class StarMediator
{
public:
	~StarMediator(){}
	virtual void reqestClone(Star* starclone)=0;
};

#endif