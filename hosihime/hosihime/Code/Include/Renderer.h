#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <gslib.h>
#include <string>
#include <map>
class Renderer
{
public:
	Renderer(){ container.clear(); }
	~Renderer(){}
	void LoadTextrue(const std::string& name,
		const GSenum colorKeyMode = GS_TEXCOLOR_KEY_DISABLE,
		const std::string& ps = "Textrue\\\\");
	void release();
	/*
	*テクスチャなし
	*/
	void drawFillRect(const GSvector2* _position, const GSrect* _rect, const GScolor* _color)const;
	void drawFillRect(const GSvector2* _position, const GSrect* _rect, const GSvector2* _scaling, const GScolor* _color)const;
	void drawFillRect(
		const GSvector2* _position,
		const GSrect*    _rect,
		const GSvector2* _center,
		const GSvector2* _scaling,
		GSfloat          _rotation,
		const GScolor*    _color
		)const;

	void drawTextrue(const std::string& name, const GSvector2* _position)const;
	void drawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect)const;
	void drawTextrue(const std::string& name, const GSvector2* _position, const GScolor* _color)const;
	void drawTextrue(const std::string& name, const GSvector2* _position, const GSvector2* _scaling, const GScolor* _color)const;
	void drawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect, const GScolor* _color)const;
	void drawTextrue(
		const std::string& name,
		const GSvector2* _position,
		const GSrect*    _rect,
		const GSvector2* _center,
		const GSvector2* _scaling,
		GSfloat          _rotation,
		const GScolor*    _color
		)const;
	/*
	GS_FONT_NORMAL 何もしない
	GS_FONT_BOLD   太字
	GS_FONT_ITALIC イタリック
	GS_FONT_UNDERLINE 下線
	GS_FONT_STRIKEOUT 打消し線
	|(ビットOR演算子)で複数重ねられる　
	*/
	void drawString(const std::string& text, const GSvector2* _position, const GSuint size,
		const GScolor* _color = &GScolor(1, 1, 1, 1), const GSbitfield& fontcode = GS_FONT_NORMAL,
		const char* fonstname = "MS ゴシック")const;

	void initBlendFunc()const;
	void additionBlend()const;
	void drawTextrueScroll(const std::string& name, const GSrect& s, const GSrect& t)const;
	void drawBlurTextrue(
		const std::string& name,
		const GSvector2& _position,
		const GSvector2* _center,
		const GSvector2& velocity,
		float angle,
		unsigned int maxSheet
		)const;
	void drawNumber(
		const std::string& name,
		const GSvector2& _position,
		float width,
		float height,
		int point,
		const GScolor* _color=&GScolor(1,1,1,1))const;
	void drawTimer(
		const std::string& name,
		const GSvector2& _position,
		float width,
		float height,
		int point,
		const GScolor* _color = &GScolor(1, 1, 1, 1))const;
private:
	//2d描画
	void disables()const;
	void draw2DSetting()const;
	void setParameter(
		const GSvector2* pCenter,
		const GSvector2* pScaling,
		GSfloat          fRotation,
		const GSvector2* pTranslation,
		const GScolor*    pColor)const;
	const GSrect getTexCoord(const GSrect* rect, GLsizei sTexWidth, GLsizei sTexHeight)const;
	const GSvector2 getTexSize(const GSrect* rect, GLsizei sTexWidth, GLsizei sTexHeight)const;
	void drawQuad(const GSrect& rTexCoord, const GSvector2& size)const;
	void drawFillRectangle(
		const GSrect*    pSrcRect,
		const GSvector2* pCenter,
		const GSvector2* pScaling,
		GSfloat          fRotation,
		const GSvector2* pTranslation,
		const GScolor*    pColor
		) const;
	void drawSprite2D(
		GSuint           uTextureID,
		const GSrect*    pSrcRect,
		const GSvector2* pCenter,
		const GSvector2* pScaling,
		GSfloat          fRotation,
		const GSvector2* pTranslation,
		const GScolor*    pColor
		) const;
	//Scroll
	void drawSprite2DScroll(GSuint uTextureID, const GSrect& s, const GSrect& t) const;
	void drawQuadScroll(const GSrect& s, const GSrect& t, const GSvector2& size)const;
private:
	std::map<const std::string, GSuint> container;
};
#endif