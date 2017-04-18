/******************************************************************************/
/*!
\file   M5ResourceManager.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/16

Class to help load graphics resources such as textures, shaders and meshes.
For now it only loads textures of type tga.
*/
/******************************************************************************/
#ifndef M5RESOURCE_MANAGER_H
#define M5RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>


//! Class to Load Resources and hold the associated resource ids used in the game.
class M5ResourceManager
{
public:
	~M5ResourceManager(void);
	int LoadTexture(const char* fileName);
	void UpdateTextureCount(int textureID);
	void UnloadTexture(int textureID);
	void Clear(void);

private:
	/*!A struct to hold loaded textures and ids so they be placed in a map together*/
	struct M5LoadedTexture
	{
		M5LoadedTexture(const std::string& str, int newID);
		std::string fileName; //!< The name of the loaded texture
		int id;               //!< GFX API's return id for this texture
		int count;            //!< The number of times this texture has been loaded.
	};

	//! Typedef Container to hold loaded textures
	typedef std::unordered_map<std::string, M5LoadedTexture> M5TextureMap;
	//! typedef for my texturemap interators
	typedef M5TextureMap::iterator M5TextureMapItor;
	//! Map of ids to loadedtexture info
	M5TextureMap m_textureMap;
};


#endif //M5RESOURCE_MANAGER_H