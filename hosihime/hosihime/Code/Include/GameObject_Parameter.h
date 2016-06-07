#ifndef _GAMEOBJECT_PARAMETER_H_
#define _GAMEOBJECT_PARAMETER_H_
#include <GSvector2.h>
#include <string>
#include "MyRectangle.h"
#include "GAMEOBJ_TYPE.h"
typedef struct GameObject_Parameter
{
	GameObject_Parameter()
		:textrue(""),
		position(GSvector2(0,0)),
		viewSize(GSvector2(0, 0)),
		rect(MyRectangle(0,0,0,0)),
		type(SPACE)
	{
	}
	GameObject_Parameter(
		const std::string& textrue,
		const GSvector2& position,
		const GSvector2& viewSize,
		const MyRectangle& rect,
		const GAMEOBJ_TYPE type)
		:textrue(textrue), 
		position(position),
		viewSize(viewSize),
		rect(rect),
		type(type)
	{
	}
	GameObject_Parameter(const GameObject_Parameter& param)
		:textrue(param.textrue),
		position(param.position),
		viewSize(param.viewSize),
		rect(param.rect),
		type(param.type)
	{
	}
	std::string textrue;//�e�N�X�`����
	GSvector2 position;//�ʒu
	GSvector2 viewSize;//�����ڂ̃T�C�Y
	MyRectangle rect;//�����蔻��
	GAMEOBJ_TYPE type;//�I�u�W�F�N�g�̃^�C�v
}Parameter;

#endif