/******************************************************************************/
/*!
\file   GfxComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/20

Base graphics component.  For now it just contains a texture.
*/
/******************************************************************************/
#ifndef GFX_COMPONENT
#define GFX_COMPONENT

#include "M5Component.h"

enum class DrawSpace
{
	DS_WORLD,
	DS_HUD
};

//!< Base graphics component.  For now it just contains a texture.
class GfxComponent : public M5Component
{
public:
	GfxComponent(void);
	~GfxComponent(void);
	void Draw(void) const;
	virtual void Update(float dt);
	virtual GfxComponent* Clone(void) const;
	virtual void FromFile(M5IniFile& iniFile);
	void SetTextureID(int id);
	int  GetTextureID(void) const;
	void SetTexture(const char* fileName);
	void SetDrawSpace(DrawSpace drawSpace);
private:
	int       m_textureID;  //!< Texture id loaded from graphics.
	float     m_texScaleX;
	float     m_texScaleY;
	float     m_texTransX;
	float     m_texTransY;
	DrawSpace m_drawSpace;  //!The space to draw in
};

#endif // !GFX_COMPONENT

