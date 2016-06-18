#include "Scroll.h"
#include "Calculate.h"

Scroll::Scroll(float widht, float height, const GSvector2& maxMapSize,int stageNo)
:stageNo(stageNo),
windowSize(0, 0, widht, height),
maxMapsize(maxMapSize),
s(0, 0, 1, 1), t(0, 1, 1, 0)
{
}
void Scroll::initialize(const GSvector2& moving)
{
	movingAmount = moving;
	isStart = true;
	mode = MODE_OMNIDIRECTIONAL;
}
void Scroll::draw(const Renderer& renderer)
{
	renderer.DrawTextrueScroll("space"+std::to_string(stageNo)+".bmp", s, t);
}
//ウィンドウの中にあるか
const bool Scroll::isInsideWindow(const GSvector2& pos, const GSvector2& size)const
{
	MyRectangle rect(pos, size);
	return rect.intersects(&windowSize);
}
void Scroll::backGroundScroll(const GSvector2& speed)
{
	scroll_st += speed;

	Calculate<float>calc;
	GSvector2 oneVec(1.0f, 1.0f);
	scroll_st = calc.wrap(scroll_st, oneVec*-1.0f, oneVec);

	// 横 	
	s.left = 1.0f + scroll_st.x;
	s.top = 1.0f + scroll_st.x;
	s.right = scroll_st.x;
	s.bottom = scroll_st.x;
	// 縦
	t.left = scroll_st.y;
	t.top = 1.0f + scroll_st.y;
	t.right = 1.0f + scroll_st.y;
	t.bottom = scroll_st.y;
}
//Scroll処理
void Scroll::moving(const GSvector2&  position, const GSvector2& offset)
{
	if (isStop()){ return; }
	float alpha = gsFrameTimerGetTime()*0.1f;
	GSvector2 lerp = movingAmount.lerp(position + offset, alpha);

	//マップのサイズにクランプ
	GSvector2 msize = maxMapsize - windowSize.getSize();
	Calculate<int>calc;
	lerp = calc.clamp(lerp, GSvector2(0, 0), msize);

	lerp *= mode;
	//差分確保
	GSvector2 margin = movingAmount - lerp;
	//移動量加算
	movingAmount = lerp;

	/**
	*差分をテクスチャサイズに変換
	*/
	margin /= windowSize.getSize();
	//上下speed反転
	margin.y *= -1.0f;
	backGroundScroll(margin);
}
//const GSvector2& Scroll::getMovingAmount()const
//{
//	return movingAmount;
//}

const GSvector2 Scroll::transformViewPosition(const GSvector2& position)const
{
	return position - movingAmount;
}

void Scroll::setMode(SCROLL_MODE _mode)
{
	mode = _mode;
}
const SCROLL_MODE& Scroll::getMode()const
{
	return mode;
}

void Scroll::stop()
{
	isStart = false;
}
void Scroll::start()
{
	isStart = true;
}
bool Scroll::isStop()
{
	return !isStart;
}