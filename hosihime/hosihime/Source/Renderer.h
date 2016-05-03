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
	GS_FONT_NORMAL �������Ȃ�
	GS_FONT_BOLD   ����
	GS_FONT_ITALIC �C�^���b�N
	GS_FONT_UNDERLINE ����
	GS_FONT_STRIKEOUT �ŏ�����
	|(�r�b�gOR���Z�q)�ŕ����d�˂���@
	*/
	void DrawString(const std::string& text, const GSvector2* _position, const GSuint size,
		const GScolor* _color = &GScolor(1, 1, 1, 1), const GSbitfield& fontcode = GS_FONT_NORMAL,
		const char* fonstname="MS �S�V�b�N");
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