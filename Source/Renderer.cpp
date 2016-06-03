#include "Renderer.h"
#include "game.h"
void Renderer::LoadTextrue(const std::string& name, const GSenum colorKeyMode, const std::string& ps)
{
	std::string name_ps = ps + name;
	gsTextureColorKeyMode(colorKeyMode);
	gsLoadTexture(container.size(),name_ps.c_str());
	container[name] = container.size();
}
void Renderer::Release()
{
	for (auto itr = container.begin(); itr != container.end(); ++itr) 
	{
		gsDeleteTexture(itr->second);
	}
	container.clear();
}
void Renderer::DrawSprite2D(
	GSuint           uTextureID,
	const GSrect*    pSrcRect,
	const GSvector2* pCenter,
	const GSvector2* pScaling,
	GSfloat          fRotation,
	const GSvector2* pTranslation,
	const GScolor*    pColor
	)
{
	GSrect rTexCoord;
	GLfloat fWidth;
	GLfloat fHeight;
	GLsizei sTexWidth;
	GLsizei sTexHeight;
	GScolor CurrentColor;
	
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glGetFloatv(GL_CURRENT_COLOR, (GLfloat*)&CurrentColor);
	gsBindTexture(uTextureID);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH,WINDOW_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	if (pTranslation != NULL)
	{
		glTranslatef(pTranslation->x, pTranslation->y, 0);
	}
	glRotatef(fRotation, 0, 0, 1);
	if (pScaling != NULL)
	{
		glScalef(pScaling->x, pScaling->y, 0);
	}
	if (pCenter != NULL)
	{
		glTranslatef(-pCenter->x, -pCenter->y, 0);
	}
	if (pColor != NULL)
	{
		glColor4fv((GLfloat*)pColor);
	}
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sTexWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sTexHeight);

	if (pSrcRect != NULL)
	{
		rTexCoord.left = pSrcRect->left / sTexWidth;
		rTexCoord.top = pSrcRect->top / sTexHeight;
		rTexCoord.right = pSrcRect->right / sTexWidth;
		rTexCoord.bottom = pSrcRect->bottom / sTexHeight;

		fWidth = ABS(pSrcRect->right - pSrcRect->left);
		fHeight = ABS(pSrcRect->bottom - pSrcRect->top);
	}
	else
	{
		rTexCoord.left = 0;
		rTexCoord.top = 0;
		rTexCoord.right = 1;
		rTexCoord.bottom = 1;
		fWidth = (GSfloat)sTexWidth;
		fHeight = (GSfloat)sTexHeight;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(rTexCoord.left, rTexCoord.top);
	glVertex2f(0, 0);
	glTexCoord2f(rTexCoord.left, rTexCoord.bottom);
	glVertex2f(0, fHeight);
	glTexCoord2f(rTexCoord.right, rTexCoord.bottom);
	glVertex2f(fWidth, fHeight);
	glTexCoord2f(rTexCoord.right, rTexCoord.top);
	glVertex2f(fWidth, 0);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor4fv((GLfloat*)&CurrentColor);
	glPopAttrib();
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position)
{
	DrawSprite2D(container[name], NULL, NULL, NULL, NULL, _position, &GScolor(1, 1, 1, 1));
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect)
{
	DrawSprite2D(container[name], _rect, NULL, NULL, NULL, _position, &GScolor(1, 1, 1, 1));
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GScolor* _color)
{
	DrawSprite2D(container[name], NULL, NULL, NULL, NULL, _position, _color);
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSvector2* _scaling, const GScolor* _color)
{
	DrawSprite2D(container[name], NULL, NULL, _scaling, NULL, _position, _color);
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect, const GScolor* _color)
{
	DrawSprite2D(container[name], _rect, NULL, NULL, NULL, _position, _color);
}
void Renderer::DrawTextrue(
	const std::string& name,
	const GSvector2* _position,
	const GSrect*    _rect,
	const GSvector2* _center,
	const GSvector2* _scaling,
	GSfloat _rotation,
	const GScolor* _color
	)
{
	DrawSprite2D(container[name], _rect, _center, _scaling, _rotation, _position, _color);
}
void Renderer::DrawString(const std::string& text, const GSvector2* _position, const GSuint size,
	const GScolor* _color, const GSbitfield& fontcode,const char* fontname)
{
	gsFontParameter(fontcode,size,fontname);
	glColor4f(_color->r, _color->g, _color->b, _color->a);
	gsTextPos(_position->x, _position->y);
	gsDrawText(text.c_str());
}
