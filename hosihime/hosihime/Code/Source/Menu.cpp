#include "Menu.h"
#include "Calculate.h"
#include "Device.h"
Menu::Menu(Device& device)
	:device(device), index(0)
{
}

void Menu::Init()
{
	isEnd = false;
	index = 0;
}
void Menu::Update()
{
	const Input input = device.getInput();
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
void Menu::Draw(const Renderer& renderer)
{
	renderer.DrawTextrue("title.bmp", &GSvector2(0, 0));
	renderer.DrawTextrue("titletext.bmp", &GSvector2(200, 120));
	const GSvector2 ps[3] =
	{
		GSvector2(450, 350),
		GSvector2(450, 450),
		GSvector2(450, 550)
	};
	const std::string tex[3] =
	{
		"gs",
		"operationText",
		"credit"
	};
	for (int i = 0; i <3; i++)
	{
		renderer.DrawTextrue(tex[i] +"_g.bmp", &ps[i]);
	}
	//���ݑI�����Ă�����̂�\��
	renderer.DrawTextrue(tex[index] + ".bmp", &ps[index]);
}
void Menu::Finish()
{

}
Scene Menu::Next()
{
	Scene scenes[3] =
	{
		//�Q�[���v���C��
		MODE_GAMEPLAY,
		//���������߂���(���̓G���f�B���O�֔��)
		MODE_ENDING,
		//������������ꗗ�ցi���̓G���f�B���O�֔�ԁj
		MODE_ENDING,
	};
	return scenes[index];
}
bool Menu::IsEnd()
{
	return isEnd;
}