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
#include <algorithm>

/******************************************************************************/
/*!
Construtor for GFX component.  Sets default values 
*/
/******************************************************************************/
GfxComponent::GfxComponent(void):
	M5Component(CT_GfxComponent),
	m_textureID(0),
	m_texScaleX(1),
	m_texScaleY(1),
	m_texTransX(0),
	m_texTransY(0),
	m_drawSpace(DrawSpace::DS_WORLD)
{
}
/******************************************************************************/
/*!
Destructor for component.  Unregisters from graphics enigne.
*/
/******************************************************************************/
GfxComponent::~GfxComponent(void)
{
	M5Gfx::UnloadTexture(m_textureID);
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
	M5Gfx::SetTextureCoords(m_texScaleX, m_texScaleY, 0, m_texTransX, m_texTransY);
	M5Gfx::SetTexture(m_textureID);
	//M5Gfx::setT
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
Clones the current GfxComponent and registers it with the GfxEngine.

\return
A new GfxComponent that is a clone of this one
*/
/******************************************************************************/
GfxComponent* GfxComponent::Clone(void) const
{
	//Allocates new object and copies data
	GfxComponent* pNew = new GfxComponent;
	pNew->m_pObj = m_pObj;
	pNew->SetTextureID(m_textureID);
	pNew->m_drawSpace = m_drawSpace;
	pNew->m_texScaleX = m_texScaleX;
	pNew->m_texScaleY = m_texScaleY;
	pNew->m_texTransX = m_texTransX;
	pNew->m_texTransY = m_texTransY;

	if (m_drawSpace == DrawSpace::DS_WORLD)
		M5Gfx::RegisterWorldComponent(pNew);
	else
		M5Gfx::RegisterHudComponent(pNew);

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
	if (m_textureID != 0)
	{
		//unregiester, regiester with gfxEngine
		M5Gfx::UnloadTexture(m_textureID);
	}
	M5Gfx::UpdateTextureCount(id);
	m_textureID = id;
}
/******************************************************************************/
/*!
Sets the texture id by loading the file via the graphics engine

\param [in] id
The new texture id for this component
*/
/******************************************************************************/
void GfxComponent::SetTexture(const char* fileName)
{
	if (m_textureID != 0)
	{
		//unregiester, regiester gfxengine
		M5Gfx::UnloadTexture(m_textureID);
	}
	m_textureID = M5Gfx::LoadTexture(fileName);
}
/******************************************************************************/
/*!
Allows users to set the Drawspace.  This will unregiseter from the opposite 
space if needed.

\param [in] drawSpace
The new drawSpace to draw in
*/
/******************************************************************************/
void GfxComponent::SetDrawSpace(DrawSpace drawSpace)
{
	M5Gfx::UnregisterComponent(this);
	if (drawSpace == DrawSpace::DS_WORLD)
		M5Gfx::RegisterWorldComponent(this);
	else
		M5Gfx::RegisterHudComponent(this);
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
	//Get texture
	std::string path("Textures\\");
	std::string fileName;
	iniFile.SetToSection("GfxComponent");
	iniFile.GetValue("texture", fileName);
	iniFile.GetValue("texScaleX", m_texScaleX);
	iniFile.GetValue("texScaleY", m_texScaleY);
	iniFile.GetValue("texTransX", m_texTransX);
	iniFile.GetValue("texTransY", m_texTransY);


	path += fileName;
	if (m_textureID != 0)
		M5Gfx::UnloadTexture(m_textureID);
	m_textureID = M5Gfx::LoadTexture(path.c_str());

	//Get drawspace
	std::string drawSpace;
	iniFile.GetValue("drawSpace", drawSpace);

	//Note, should be lowercase, otherwise it will be part of hud
	if (drawSpace == "world")
		m_drawSpace = DrawSpace::DS_WORLD;
	else
		m_drawSpace = DrawSpace::DS_HUD;
}
/******************************************************************************/
/*!
Returns the textureId used by the Gfx Component
*/
/******************************************************************************/
int GfxComponent::GetTextureID(void) const
{
	return m_textureID;
}