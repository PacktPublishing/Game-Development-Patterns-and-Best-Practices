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
#include "GfxComponent.h"
#include "M5Gfx.h"
#include "M5Mtx44.h"
#include "M5Object.h"
#include "M5IniFile.h"
#include <string>

/******************************************************************************/
/*!
Construtor for GFX component.  Sets default values 
*/
/******************************************************************************/
GfxComponent::GfxComponent(void):
	M5Component(CT_GfxComponent),
	m_textureID(0)
{
}
/******************************************************************************/
/*!
Destructor for component.  Unregisters from graphics enigne.
*/
/******************************************************************************/
GfxComponent::~GfxComponent(void)
{
	M5Gfx::UnregisterComponent(this);
}
/******************************************************************************/
/*!
This component know how to draw itself.
*/
/******************************************************************************/
void GfxComponent::Draw(void) const
{
	M5Mtx44 world;
	world.MakeTransform(m_pObj->scale, 
		m_pObj->rotation, 
		m_pObj->pos, 
		0);
	M5Gfx::SetTexture(m_textureID);
	M5Gfx::Draw(world);
}
/******************************************************************************/
/*!
There is nothing to update.  We could have the object draw itself here,
but I have chosento let graphics take care of all drawing.

\param [in] dt
The time in seconds since the last frame.
*/
/******************************************************************************/
void GfxComponent::Update(float /*dt*/)
{
}
/******************************************************************************/
/*!
Shutdown function clears all game objects and destroys prototypes.

\return
A new GfxComponent that is a clone of this one
*/
/******************************************************************************/
M5Component* GfxComponent::Clone(void)
{
	GfxComponent* pNew = new GfxComponent;
	pNew->m_pObj = m_pObj;
	pNew->m_textureID = m_textureID;

	return pNew;
}
/******************************************************************************/
/*!
Allows users to set the texture id.

\param [in] id
The new texture id for this component
*/
/******************************************************************************/
void GfxComponent::SetTextureID(int id)
{
	m_textureID = id;
}
/******************************************************************************/
/*!
Reads in data from a preloaded ini file.

\param [in] iniFile
The preloaded inifile to read from.
*/
/******************************************************************************/
void GfxComponent::FromFile(M5IniFile& iniFile)
{
	std::string path("Textures\\");
	std::string fileName;
	iniFile.SetToSection("GfxComponent");
	iniFile.GetValue("texture", fileName);
	path += fileName;
	m_textureID = M5Gfx::LoadTexture(path.c_str());
}