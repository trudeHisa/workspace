#include "Title.h"
//�^�C�g���N���X�R���X�g���N�^
#include "Point.h"
#include "Calculate.h"
#include "Input.h"
Title::Title(const Input& input)
	:input(input)
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
	if (boolSpace)
	{
		if (input.getUpTrigger())
		{
			index -= 1;
		}

		if (input.getDownTrigger())
		{
			index += 1;
		}
		Calculate<int>calc;
		index = calc.wrap(index, 0, 3);
		isEnd = input.getActionTrigger();
	}

	//�X�y�[�X�L�[�������ƃ��j���[��\��
	if (gsGetKeyState(GKEY_SPACE) && !boolSpace){

		boolSpace = true;
	}
}
void Title::Draw(Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titlename.bmp", &GSvector2(200, 120));
	const GSvector2 ps[3] =
	{
		GSvector2(450, 350),
		GSvector2(450, 450),
		GSvector2(450, 550)
	};
	if (!boolSpace)
	{
		renderer.DrawTextrue("spacename.bmp", &GSvector2(480, 540));
	}
	else{

		renderer.DrawTextrue("gs_g.bmp", &ps[0]);
		renderer.DrawTextrue("turt_g.bmp", &ps[1]);
		renderer.DrawTextrue("credit_g.bmp", &ps[2]);
		const std::string tex[3] =
		{
			"gs.bmp",
			"turt.bmp",
			"credit.bmp"
		};

		//���ݑI�����Ă�����̂�\��
		renderer.DrawTextrue(tex[index], &ps[index]);
	}
}
void Title::Finish()
{
}
Scene Title::Next()
{
	Scene ns;
	switch (index)
	{
	case 0:
		//�Q�[���v���C��
		ns = MODE_GAMEPLAY;
		break;
	case 1:
		//���������߂���(���̓G���f�B���O�֔��)
		ns = MODE_ENDING;
		break;
	case 2:
		//������������ꗗ�ցi���̓G���f�B���O�֔�ԁj
		ns = MODE_ENDING;
		break;
	}
	return ns;
}
bool Title::IsEnd()
{
	return isEnd;
}