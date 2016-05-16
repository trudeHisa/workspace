#include "Title.h"
//�^�C�g���N���X�R���X�g���N�^
#include "Point.h"
int index;//�I�����Ǘ�
bool boolSpace;//
Title::Title()
{
}
Title::~Title()
{
}
void Title::Init()
{
	index = 0;
	boolSpace = false;//�u�X�y�[�X�L�[�������Ă��������v�̊Ǘ��Bfalse�ŕ\��
	isEnd = false;
}
void Title::Update()
{
	//���j���[�I���̏���
	if (boolSpace){
		if (gsGetKeyState(GKEY_UPARROW)){
			if (gsGetKeyTrigger(GKEY_UPARROW)){
				index -= 1;
			}
		}
		if (gsGetKeyState(GKEY_DOWNARROW)){
			if (gsGetKeyTrigger(GKEY_DOWNARROW)){
				index += 1;
			}
		}
		if (index > 2)index = 0;
		if (index < 0)index = 2;
		isEnd = gsGetKeyTrigger(GKEY_SPACE);
}

	//�X�y�[�X�L�[�������ƃ��j���[��\��
	if (gsGetKeyState(GKEY_SPACE)&& !boolSpace){
		
		boolSpace = true;
	}
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titlename.bmp", &GSvector2(200,120));
	if (!boolSpace){
		renderer.DrawTextrue("spacename.bmp", &GSvector2(480, 540));
}
	else{
		
		renderer.DrawTextrue("gs_g.bmp", &GSvector2(450, 350));
		renderer.DrawTextrue("turt_g.bmp", &GSvector2(450, 450));
		renderer.DrawTextrue("credit_g.bmp", &GSvector2(450, 550));
		//���ݑI�����Ă�����̂�\��
		switch (index)
		{
		case 0:
			//�Q�[���X�^�[�g
			renderer.DrawTextrue("gs.bmp", &GSvector2(450, 350));
			break;
		case 1:
			//���������߂�
			renderer.DrawTextrue("turt.bmp", &GSvector2(450, 450));
			break;
		case 2:
			//������������ꗗ
			renderer.DrawTextrue("credit.bmp", &GSvector2(450, 550));
			break;
		}
	}
}
void Title::Finish()
{
}
Scene Title::Next()
{
	
	switch (index)
	{
	case 0:
		//�Q�[���v���C��
	return MODE_GAMEPLAY;
		break;
	case 1:
		//���������߂���(���̓G���f�B���O�֔��)
		return MODE_ENDING;
		break;
	case 2:
		//������������ꗗ�ցi���̓G���f�B���O�֔�ԁj
		return MODE_ENDING;
		break;
	}
	
}
bool Title::IsEnd()
{
	return isEnd;
}