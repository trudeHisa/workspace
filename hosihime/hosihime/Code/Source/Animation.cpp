#include "Animation.h"

Animation::Animation(AnimationTimer& timer)
:cellno(0), timer(timer)
{
}

Animation::~Animation()
{
	cells.clear();
}
void Animation::addCell(const std::string& initial, int line, int peace, int width, int heigth)
{
	for (int i = 0; i < peace; i++)
	{
		float x = i*width;
		float y = (line - 1)*heigth;
		cells[createCellKey(initial, i)] = GSrect(x, y, x + width, y + heigth);
	}
	currentCell = cells.begin()->first;
}
void Animation::updata(const std::string& initial)
{
	previousCell = currentCell;
	currentCell = createCellKey(initial, cellno);
	if (currentCell != previousCell)
	{
		currentCell = createCellKey(initial, 0);
	}
	if (!timer.isZero())
	{
		return;
	}
	timer.reset();
	cellno += 1;
	currentCell = createCellKey(initial, cellno);
	if (cells.count(currentCell) == 0)
	{
		cellno = 0;
		currentCell = createCellKey(initial, cellno);
	}
}
void Animation::draw(const  Renderer& renderer, const std::string& name, const GSvector2* position)
{
	float l = cells[currentCell].left;
	float t = cells[currentCell].top;
	float r = cells[currentCell].right;
	float b = cells[currentCell].bottom;
	renderer.DrawString("l:"+std::to_string(l),&GSvector2(300,10),20);
	renderer.DrawString("t:" + std::to_string(t), &GSvector2(300, 30), 20);
	renderer.DrawString("r:" + std::to_string(r), &GSvector2(300, 50), 20);
	renderer.DrawString("b:" + std::to_string(b), &GSvector2(300, 70), 20);

	renderer.DrawTextrue(name, position, &cells[currentCell]);
}
const std::string Animation::createCellKey(const std::string& initial, int no)const
{
	return initial + std::to_string(no);
}