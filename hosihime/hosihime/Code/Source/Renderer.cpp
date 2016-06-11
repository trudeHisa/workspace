#include "Renderer.h"
#include "game.h"
void Renderer::LoadTextrue(const std::string& name, const GSenum colorKeyMode, const std::string& ps)
{
	std::string name_ps = ps + name;
	gsTextureColorKeyMode(colorKeyMode);
	gsLoadTexture(container.size(), name_ps.c_str());
	container.insert(std::pair<const std::string, GSuint>(name, container.size()));
}
void Renderer::Release()
{
	for (auto itr = container.begin(); itr != container.end(); ++itr)
	{
		gsDeleteTexture(itr->second);
	}
	container.clear();
}
void Renderer::DrawFillRectangle(
	const GSrect*    pSrcRect,
	const GSvector2* pCenter,
	const GSvector2* pScaling,
	GSfloat          fRotation,
	const GSvector2* pTranslation,
	const GScolor*    pColor
	) const
{
	disables();
	GScolor CurrentColor;
	glGetFloatv(GL_CURRENT_COLOR, (GLfloat*)&CurrentColor);

	draw2DSetting();
	setParameter(pCenter, pScaling, fRotation, pTranslation, pColor);

	GSvector2 texSize = getTexSize(pSrcRect,0,0);
	GSrect uv(0,0,1,1);

	drawQuad(uv,texSize);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor4fv((GLfloat*)&CurrentColor);
	glPopAttrib();
}

void Renderer::DrawSprite2D(
	GSuint           uTextureID,
	const GSrect*    pSrcRect,
	const GSvector2* pCenter,
	const GSvector2* pScaling,
	GSfloat          fRotation,
	const GSvector2* pTranslation,
	const GScolor*    pColor
	)const
{
	disables();
	GScolor CurrentColor;
	glGetFloatv(GL_CURRENT_COLOR, (GLfloat*)&CurrentColor);
	gsBindTexture(uTextureID);

	draw2DSetting();
	setParameter(pCenter,pScaling,fRotation,pTranslation,pColor);

	GLsizei sTexWidth;
	GLsizei sTexHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sTexWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sTexHeight);

	GSrect rTexCoord = getTexCoord(pSrcRect,sTexWidth,sTexHeight);
	GSvector2 texSize = getTexSize(pSrcRect, sTexWidth, sTexHeight);

	drawQuad(rTexCoord,texSize);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor4fv((GLfloat*)&CurrentColor);
	glPopAttrib();
}
void Renderer::setParameter(const GSvector2* pCenter,
	const GSvector2* pScaling,
	GSfloat          fRotation,
	const GSvector2* pTranslation,
	const GScolor*    pColor)const
{
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
}
void Renderer::draw2DSetting()const
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}
void Renderer::disables()const
{
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}
const GSrect Renderer::getTexCoord(const GSrect* rect, GLsizei sTexWidth, GLsizei sTexHeight)const
{
	GSrect texCoord;
	if (rect != NULL)
	{
		texCoord.left = rect->left / sTexWidth;
		texCoord.top = rect->top / sTexHeight;
		texCoord.right = rect->right / sTexWidth;
		texCoord.bottom = rect->bottom / sTexHeight;
		return texCoord;
	}
	texCoord.left = 0;
	texCoord.top = 0;
	texCoord.right = 1;
	texCoord.bottom = 1;
	return texCoord;
}
const GSvector2 Renderer::getTexSize(const GSrect* rect, GLsizei sTexWidth, GLsizei sTexHeight)const
{
	GSvector2 size;
	if (rect != NULL)
	{
		size.x = ABS(rect->right - rect->left);
		size.y = ABS(rect->bottom - rect->top);
		return size; 
	}
	size.x = (GSfloat)sTexWidth;
	size.y = (GSfloat)sTexHeight;
	return size;
}
void Renderer::drawQuad(const GSrect& rTexCoord,const GSvector2& size)const
{
	glBegin(GL_QUADS);
	glTexCoord2f(rTexCoord.left, rTexCoord.top);
	glVertex2f(0, 0);
	glTexCoord2f(rTexCoord.left, rTexCoord.bottom);
	glVertex2f(0, size.y);
	glTexCoord2f(rTexCoord.right, rTexCoord.bottom);
	glVertex2f(size.x, size.y);
	glTexCoord2f(rTexCoord.right, rTexCoord.top);
	glVertex2f(size.x, 0);
	glEnd();
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position)const
{
	DrawSprite2D(container.at(name), NULL, NULL, NULL, NULL, _position, &GScolor(1, 1, 1, 1));
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect)const
{
	DrawSprite2D(container.at(name), _rect, NULL, NULL, NULL, _position, &GScolor(1, 1, 1, 1));
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GScolor* _color)const
{
	DrawSprite2D(container.at(name), NULL, NULL, NULL, NULL, _position, _color);
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSvector2* _scaling, const GScolor* _color)const
{
	DrawSprite2D(container.at(name), NULL, NULL, _scaling, NULL, _position, _color);
}
void Renderer::DrawTextrue(const std::string& name, const GSvector2* _position, const GSrect* _rect, const GScolor* _color)const
{
	DrawSprite2D(container.at(name), _rect, NULL, NULL, NULL, _position, _color);
}
void Renderer::DrawTextrue(
	const std::string& name,
	const GSvector2* _position,
	const GSrect*    _rect,
	const GSvector2* _center,
	const GSvector2* _scaling,
	GSfloat _rotation,
	const GScolor* _color
	)const
{
	DrawSprite2D(container.at(name), _rect, _center, _scaling, _rotation, _position, _color);
}
void Renderer::DrawString(const std::string& text, const GSvector2* _position, const GSuint size,
	const GScolor* _color, const GSbitfield& fontcode, const char* fontname)const
{
	gsFontParameter(fontcode, size, fontname);
	glColor4f(_color->r, _color->g, _color->b, _color->a);
	gsTextPos(_position->x, _position->y);
	gsDrawText(text.c_str());
}

void Renderer::InitBlendFunc()const
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Renderer::AdditionBlend()const
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
};
void Renderer::DrawTextrueScroll(const std::string& name, const GSrect& s, const GSrect& t)const
{
	DrawSprite2DScroll(container.at(name),s,t);
}
void Renderer::DrawSprite2DScroll(GSuint uTextureID, const GSrect& s, const GSrect& t) const
{
	disables();
	GScolor CurrentColor;
	glGetFloatv(GL_CURRENT_COLOR, (GLfloat*)&CurrentColor);
	gsBindTexture(uTextureID);
	draw2DSetting();
	GLsizei sTexWidth;
	GLsizei sTexHeight;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sTexWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sTexHeight);
	GSvector2 texSize = getTexSize(0, sTexWidth, sTexHeight);

	drawQuadScroll(s,t, texSize);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glColor4fv((GLfloat*)&CurrentColor);
	glPopAttrib();
}
void Renderer::drawQuadScroll(const GSrect& s, const GSrect& t, const GSvector2& size)const
{
	glBegin(GL_QUADS);
	glTexCoord2f(s.left, t.left);
	glVertex2f(0, 0);
	glTexCoord2f(s.top, t.top);
	glVertex2f(0, size.y);
	glTexCoord2f(s.right, t.right);
	glVertex2f(size.x, size.y);
	glTexCoord2f(s.bottom, t.bottom);
	glVertex2f(size.x, 0);
	glEnd();
}
void Renderer::DrawFillRect(const GSvector2* _position, const GSrect* _rect, const GScolor* _color)const
{
	DrawFillRectangle(_rect, NULL, NULL, NULL, _position, _color);
}
void Renderer::DrawFillRect(const GSvector2* _position, const GSrect* _rect, const GSvector2* _scaling, const GScolor* _color)const
{
	DrawFillRectangle(_rect, NULL, _scaling, NULL, _position, _color);
}
void Renderer::DrawFillRect(
	const GSvector2* _position,
	const GSrect*    _rect,
	const GSvector2* _center,
	const GSvector2* _scaling,
	GSfloat          _rotation,
	const GScolor*    _color
	)const
{
	DrawFillRectangle(_rect, _center, _scaling, _rotation, _position, _color);
}