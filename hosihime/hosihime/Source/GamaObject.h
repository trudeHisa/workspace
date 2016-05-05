/*
GameObject.h
*/
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "GAMEOBJ_TYPE.h"
#include "Renderer.h"
#include "Point.h"
#include <string>
#include "Definition.h"

class GameObject
{
public:
	GameObject(const std::string& textrue,const Point* size,
		const GAMEOBJ_TYPE type,const GSvector2* position);
	~GameObject();
	virtual void updata(MapData* mapdata) = 0;
	virtual void draw(Renderer& renderer);
	virtual void initialize();
	virtual void finish();
	const Point getSize()const;
	const GAMEOBJ_TYPE getType()const;
	const bool getIsDead()const;
	const Point getLocation()const;
	const GSvector2 getPosition()const;
protected:
	/*
	�ړ���̈ʒu�I�u�W�F�N�g������ꍇ
	�Ԃ��l�͈ړ��ł��邩�ł��Ȃ�����Ԃ�
	*/
	virtual bool nextAction(int nextPosType)=0;
	virtual void nextPosition(GSvector2* pos) = 0;//�ړ���̈ʒu��Ԃ�
	virtual const bool isNextMove(const MapData* mapdata);//�ړ��ł��邩
	//�T�C�Y���}�b�v�f�[�^�ɑ������֐�
	void mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type);
	void mapUpdata(MapData* mapdata, const Point* point, GAMEOBJ_TYPE oldPostype);	
	void castLocation(const GSvector2* pos,Point* loc);
	const bool isInSideMap(const MapData* mapdata, const Point* point)const;//�}�b�v���Ȃ�true

protected:
	std::string textrue;
	bool isDead;
	Point location;
	GSvector2 position;
	GAMEOBJ_TYPE type;
	Point size;
};
#endif