#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <gslib.h>
#include <map>
class Renderer
{
public:
	Renderer(){ container.clear(); }
	~Renderer(){}
	void LoadTextrue(const std::string& name,
		const GSenum colorKeyMode = GS_TEXCOLOR_KEY_DISABLE,
		const std::string& ps = "Textrue\\\\");
	void Release();
	void DrawTextrue(const std::string& name, const GSvector2* _position);
	void DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect);
	void DrawTextrue(const std::string& name, const GSvector2* _position, const GScolor* _color);
	void DrawTextrue(const std::string& name, const GSvector2* _position, const GSvector2* _scaling, const GScolor* _color);
	void DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect, const GScolor* _color);
	void DrawTextrue(
		const std::string& name,
		const GSvector2* _position,
		const GSrect*    _rect,
		const GSvector2* _center,
		const GSvector2* _scaling,
		GSfloat          _rotation,
		const GScolor*    _color
		);
	/*
	GS_FONT_NORMAL 何もしない
	GS_FONT_BOLD   太字
	GS_FONT_ITALIC イタリック
	GS_FONT_UNDERLINE 下線
	GS_FONT_STRIKEOUT 打消し線
	|(ビットOR演算子)で複数重ねられる　
	*/
	void DrawString(const std::string& text, const GSvector2* _position, const GSuint size,
		const GScolor* _color = &GScolor(1, 1, 1, 1), const GSbitfield& fontcode = GS_FONT_NORMAL,
		const char* fonstname="MS ゴシック");
	void InitBlendFunc()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void AdditionBlend()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

private:	
	void DrawSprite2D(
		GSuint           uTextureID,
		const GSrect*    pSrcRect,
		const GSvector2* pCenter,
		const GSvector2* pScaling,
		GSfloat          fRotation,
		const GSvector2* pTranslation,
		const GScolor*    pColor
		);
	std::map<const std::string, GSuint> container;
};
#endif