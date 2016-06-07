/*
GAMEOBJ_TYPE.h
*/
#ifndef _GAMEOBJ_TYPE_H_
#define _GAMEOBJ_TYPE_H_
enum GAMEOBJ_TYPE
{
	SPACE = 0,
	PLAYER = 100,

	STAR = 10,
	BREAKSTAR=11,
	BURNSTAR=12,
	STRA_NoMove=13,
	BREAKSTAR_NoMove = 14,
	
	RESPAWN = 20,
	PLANET = 21,
	MAGPIE=22,
	START =30, 
	GOAL =40
};

#endif