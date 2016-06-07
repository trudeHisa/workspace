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
void Animation::draw(const Renderer& renderer, const std::string& name, const GSvector2* position)
{
	renderer.DrawTextrue(name, position, &cells[currentCell]);
}
const std::string Animation::createCellKey(const std::string& initial, int no)const
{
	return initial + std::to_string(no);
}