#include "Opening.h"

#include "Device.h"
//�I�[�v�j���O�N���X�R���X�g���N�^
Opening::Opening(Device& device)
	:device(device)
{

}

Opening::~Opening()
{

}

void Opening::Init()
{
	isEnd = false;
}

void Opening::Update()
{
	isEnd = device.getInput().getActionTrigger();
}

void Opening::Draw(const Renderer& renderer)
{

}

void Opening::Finish()
{

}

Scene Opening::Next()
{
	return MODE_TITLE;
}

bool Opening::IsEnd()
{
	return isEnd;
}
