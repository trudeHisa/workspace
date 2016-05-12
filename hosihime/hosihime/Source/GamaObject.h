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
	virtual void finish(MapData* mapdata);
public:
	const Point getSize()const;
	const bool getIsDead()const;
	//�����Ȃ�true
	const bool isSameLocation(const Point& _location)const;
	const bool isSameType(GAMEOBJ_TYPE _type)const;
private:
	//mapdata�̍X�V
	void mapUpdata(MapData* mapdata, const Point* point);
	//�I�u�W�F�N�g�Ɠ������Ă��邩�H
	const bool isCollision(const MapData* mapdata, const Point* nextLocation);
protected:	
	//�ړ���̈ʒu�I�u�W�F�N�g������ꍇ�Ԃ��l�͈ړ��ł��邩�ł��Ȃ�����Ԃ�	
	virtual bool collision(int nextPosType)=0;
	//�T�C�Y���}�b�v�f�[�^�ɑ������֐�
	void mapdataAssignment(MapData* mapdata, const Point* point, GAMEOBJ_TYPE _type);	
	//pos��BLOCKSIZE�Ŋ���loc�ɑ��
	void castLocation(const GSvector2* pos,Point* loc);
	//�ړ�����
	void move(MapData* mapdata);	
	//�ړ��ł��邩
	const bool isNextMove(const MapData* mapdata, const GSvector2* nextVelcity);
	/*
	�`��p�Ɉʒu��ς���
	true�Ȃ�`��,false�Ȃ�`�悵�Ȃ�
	*/
	bool forDrawPosition(GSvector2* _position, const Scroll* scroll);
private:
	std::string textrue;
	GAMEOBJ_TYPE type;
	Point size;
protected:	
	bool isDead;
	Point location;
	GSvector2 position;
	GSvector2 velocity;
};
#endif