#include "Scroll.h"
#include "Calculate.h"

Scroll::Scroll(float widht, float height)
	:windowSize(0, 0, widht, height),
	s(0, 0, 1, 1), t(0, 1, 1, 0)
{
}
void Scroll::initialize()
{
	movingAmount = GSvector2(0, 0);
	isStart = true;
	mode = MODE_OMNIDIRECTIONAL;
}
void Scroll::updata()
{
}
void Scroll::draw(const Renderer& renderer)
{
	renderer.DrawTextrueScroll("space.bmp", s, t);
}
//ウィンドウの中にあるか
const bool Scroll::isInsideWindow(const GSvector2& pos, const GSvector2& size)const
{
	MyRectangle rect(pos, size);
	return rect.intersects(&windowSize);
}
void Scroll::st_Wrap(GSvector2* st)
{
	Calculate<float>calc;
	st->x = calc.wrap(st->x, -1.0f, 1.0f);
	st->y = calc.wrap(st->y, -1.0f, 1.0f);
}
void Scroll::backGroundScroll(const GSvector2& speed)
{
	scroll_st += speed;
	st_Wrap(&scroll_st);
	// 横 	
	//scroll_st.x = calc.wrap(scroll_ts + speed.x, -1.0f, 1.0f);
	s.left = 1.0f + scroll_st.x;
	s.top = 1.0f + scroll_st.x;
	s.right = scroll_st.x;
	s.bottom = scroll_st.x;
	// 縦
	//scroll_tt = calc.wrap(scroll_tt -speed.y , -1.0f, 1.0f);
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
	lerp *= mode;
	//差分確保
	GSvector2 margin = movingAmount - lerp;
	//移動量加算
	movingAmount = lerp;
	/**
	*差分をテクスチャサイズ(WindowSize)に変換
	*/
	margin /= windowSize.getSize();
	//上下speed反転
	margin.y *= -1.0f;
	backGroundScroll(margin);
}
const GSvector2& Scroll::getMovingAmount()const
{
	return movingAmount;
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