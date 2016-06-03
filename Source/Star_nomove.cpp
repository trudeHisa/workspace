#include "Star_nomove.h"

Star_nomove::Star_nomove()
{

}
Star_nomove::~Star_nomove()
{

}
GSvector2 Star_nomove::moving()
{
	return GSvector2(0, 0);
}
IStarMove* Star_nomove::clone()
{
	return new Star_nomove();
}