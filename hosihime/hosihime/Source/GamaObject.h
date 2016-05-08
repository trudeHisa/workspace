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
#include "Scroll.h"
class GameObject
{
public:
	GameObject(const std::string& textrue,const Point* size,
		const GAMEOBJ_TYPE type,const GSvector2* position);
	~GameObject();
	virtual void updata(MapData* mapdata) = 0;
	virtual void draw(Renderer& renderer,const Scroll* scroll);
	virtual void initialize();
	virtual void finish();
public:
	const Point getSize()const;
	const bool getIsDead()const;
	//�����Ȃ�true
	const bool isSameLocation(const Point& _location)const;
	const bool isSameType(GAMEOBJ_TYPE _type)const;

protected:
	/*
	�ړ���̈ʒu�I�u�W�F�N�g������ꍇ
	�Ԃ��l�͈ړ��ł��邩�ł��Ȃ�����Ԃ�
	*/
	virtual bool collision(int nextPosType)=0;
	//�T�C�Y���}�b�v�f�[�^�ɑ������֐�
	void mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type);
	//mapdata�̍X�V
	void mapUpdata(MapData* mapdata, const Point* point, GAMEOBJ_TYPE oldPostype);	
	//pos��BLOCKSIZE�Ŋ���loc�ɑ��
	void castLocation(const GSvector2* pos,Point* loc);
	//�ړ�����
	void move(MapData* mapdata,GAMEOBJ_TYPE oldPostype);
	//�ړ��ł��邩
	const bool isNextMove(const MapData* mapdata, const GSvector2* nextVelcity);
	//�I�u�W�F�N�g�Ɠ������Ă��邩�H
	const bool isCollision(const MapData* mapdata,const Point* nextLocation);
	//�}�b�v���Ȃ�true
	const bool isInSideMap(const MapData* mapdata, const Point* point)const;
protected:
	std::string textrue;
	bool isDead;
	Point location;
	GSvector2 position;
	GAMEOBJ_TYPE type;
	Point size;
	GSvector2 velocity;
};
#endif