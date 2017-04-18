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
#include "M5ResourceManager.h"
#include "M5Math.h"
#include "M5Debug.h"

//opengl
#include "gl/glew.h"
#include "gl/gl.h"
#include "gl/glu.h"

//standard lib
#include <cstdio> /*For opening files*/
#include <cstring> /*memcpy*/
#include <sstream>
#include <iomanip>

namespace
{
/*A struct to pass Texture data to open gl*/
struct M5Texture
{
	GLubyte* imageData;    /*Image data, up to 32bits*/
	GLuint   bitsPerPixel; /*bits count*/
	GLuint   bytesPerPixel;/*byte count*/
	GLuint   width;        /*Image width*/
	GLuint   height;       /*Image height*/
	GLuint   textureID;    /*Texture ID*/
	GLuint   format;       /*Image Type, GL_RGB, GL_RBGA*/
	GLuint   imageSize;    /*totalSize of image*/
};

/*A struct to hold information about my TGA file*/
struct M5TGAHeader
{
	GLubyte headerPart1[12];/*First 12 bytes from header*/
	GLubyte headerPart2[6]; /*Last 6 bytes from header*/
};



/******************************************************************************/
/*!
Helper function to delete data and close a file, because there are many chances
to fail in the loading process.

\param pTexture
The image data that must be deleted.

\param ppFile
A pointer to a file to close and set to 0.

\param p
The message to warn about in debug mode.
*/
/******************************************************************************/
void LoadFail(M5Texture* pTexture, FILE** ppFile, const char* p)
{
	/*In release, this parameter isn't used.*/
	p = p;

	/*Sometimes I don't need to delete the texture*/
	if (pTexture)
	{
		delete[] pTexture->imageData;
		pTexture->imageData = 0;
	}
	/*Always close the file*/
	fclose(*ppFile);
	*ppFile = 0;
	M5DEBUG_ASSERT(false, p);
}
/******************************************************************************/
/*!
Fills in the texture pointer with data from the file.

\param pTexture
a pointer to a Texture to fill in with information from the file.

\param pHeader
The header from the file to calculate texture data.

\return
True if we have a valid file, false otherwise.  If this function returns
false, no memory was allocated in pTexture->imageData.
*/
/******************************************************************************/
int UpdateTexture(M5Texture* pTexture, const M5TGAHeader* pHeader)
{
	/*const numbers for comparisons*/
	const GLuint RGB_BITS = 24;/*24 bits per pixel*/
	const GLuint RGBA_BITS = 32;/*32 bits per pixel*/

								/*Translate header info*******************************************/
								/*Width is highByte * 256 + lowByte*/
	pTexture->width = pHeader->headerPart2[1] * 256 + pHeader->headerPart2[0];
	/*Height is highByte * 256 + lowbyte*/
	pTexture->height = pHeader->headerPart2[3] * 256 + pHeader->headerPart2[2];
	/*Get bits per pixel*/
	pTexture->bitsPerPixel = pHeader->headerPart2[4];
	/*Gets bytes per pixel, 8 bits per byte */
	pTexture->bytesPerPixel = pTexture->bitsPerPixel / 8;
	/*Calculate image size*/
	pTexture->imageSize = pTexture->bytesPerPixel * pTexture->width * pTexture->height;

	/*Set our format for openGL*/
	if (pTexture->bitsPerPixel == RGB_BITS)
		pTexture->format = GL_RGB;
	else
		pTexture->format = GL_RGBA;

	/*Make sure this is a format we support*/
	/*Must have a valid width and height and must be 24 or 32 bits*/
	if ((pTexture->width <= 0) || (pTexture->height <= 0) || (pTexture->bitsPerPixel != RGB_BITS && pTexture->bitsPerPixel != RGBA_BITS))
	{
		return false;
	}

	/*Allocate image data*/
	pTexture->imageData = new GLubyte[pTexture->imageSize];

	return true;
}
/******************************************************************************/
/*!
Load an uncompressed TGA file.  This code is based on NeHes example at
nehe.gamedev.net

\param pTexture
A pointer to a texture with the image data already allocated.  It must be
deleted before return an error.

\param pFile
A pointer to an open file to read, it must be closed before returning an
error.

\return
True if the load was successful, false otherwise.  If you return false,
you must free the texture data and close the file.

*/
/******************************************************************************/
int LoadUncompressedTGA(M5Texture* pTexture, FILE* pFile)
{
	GLuint i;/*For for loop*/
	if (fread(pTexture->imageData, pTexture->imageSize, 1, pFile) == 0)
	{
		LoadFail(pTexture, &pFile, "Error Reading file");
		return false;
	}
	/*The data is read in, but is BGR, we need RGB, so swap*/
	for (i = 0; i < pTexture->imageSize; i += pTexture->bytesPerPixel)
	{
		GLubyte swapStorage = pTexture->imageData[i];
		pTexture->imageData[i] = pTexture->imageData[i + 2];
		pTexture->imageData[i + 2] = swapStorage;
	}

	return true;
}
/******************************************************************************/
/*!
Load an uncompressed TGA file.  This code is based on NeHes example at
nehe.gamedev.net

\param pTexture
A pointer to a texture with the image data already allocated.  It must be
freed before return an error.

\param pFile
A pointer to an open file to read, it must be closed before returning an
error.

\return
True if the load was successful, false otherwise.  If you return false,
you must free the texture data and close the file.

*/
/******************************************************************************/
int LoadCompressedTGA(M5Texture* pTexture, FILE* pFile)
{
	/*The number of pixels in the image*/
	GLuint pixelCount = pTexture->height * pTexture->width;
	/*The current pixel being read*/
	GLuint currentPixel = 0;
	GLuint currentByte = 0;
	GLubyte colorBuffer[4] = { 0 };/*At most 4 bytes per pixel*/

	do
	{
		/*used by my for loop to count the color packets*/
		GLubyte counter = 0;
		GLubyte chunkHeader = 0;
		/*Read in the 1 byte header*/
		if (fread(&chunkHeader, sizeof(chunkHeader), 1, pFile) == 0)
		{
			LoadFail(pTexture, &pFile, "Error Reading file");
			return false;
		}

		/*if header is < 128 it means chunkHeader specifies the nubmer of RAW
		color packets  minus 1 that follow the header*/
		if (chunkHeader < 128)
		{
			/*Add 1 to get the number of color packets*/
			++chunkHeader;

			/*make sure we won't overwrite our buffer*/
			if ((currentPixel + chunkHeader) > pixelCount)
			{
				LoadFail(pTexture, &pFile, "Invalid file.");
				return false;
			}

			/*now read in the color packets*/
			for (counter = 0; counter < chunkHeader; ++counter)
			{
				/*read one pixel*/
				if (fread(colorBuffer, 1, pTexture->bytesPerPixel, pFile) !=
					pTexture->bytesPerPixel)
				{
					LoadFail(pTexture, &pFile, "Error reading file");
					return false;
				}

				/*copy 3 or 4 bytes depending on the bytes per pixel*/
				memcpy(&pTexture->imageData[currentByte], colorBuffer,
					pTexture->bytesPerPixel);

				/*Swap r and b*/
				pTexture->imageData[currentByte] = colorBuffer[2];
				pTexture->imageData[currentByte + 2] = colorBuffer[0];

				/*increase current byte*/
				currentByte += pTexture->bytesPerPixel;
				++currentPixel;
			}/*end for loop*/
		}/*end if(chunkHeader < 128*/
		else
		{
			/*if chunkHeader > 128 it means RLE data.  The next color is
			repeated (chunkHeader - 127) times*/
			/*subtract 127*/
			chunkHeader -= 127;
			/*Attempt to read the color*/
			if (fread(colorBuffer, 1, pTexture->bytesPerPixel, pFile) !=
				pTexture->bytesPerPixel)
			{
				LoadFail(pTexture, &pFile, "Error Reading File");
				return false;
			}

			/*make sure we won't overwrite our buffer*/
			if ((currentPixel + chunkHeader) > pixelCount)
			{
				LoadFail(pTexture, &pFile, "Invalid File");
				return false;
			}

			/*copy the color, chunkHeader number of times*/
			for (counter = 0; counter < chunkHeader; ++counter)
			{
				/*copy 3 or 4 bytes depending on the bytes per pixel*/
				memcpy(&pTexture->imageData[currentByte], colorBuffer,
					pTexture->bytesPerPixel);

				/*Swap r and b*/
				pTexture->imageData[currentByte] = colorBuffer[2];
				pTexture->imageData[currentByte + 2] = colorBuffer[0];

				/*increase current byte*/
				currentByte += pTexture->bytesPerPixel;
				++currentPixel;
			}
		}/*end else*/

	} while (currentPixel < pixelCount);

	return true;
}
/******************************************************************************/
/*!
My function to start loading a TGA file.  This will decided if the texture is
compressed or uncompressed.

\attention
If the function returns true, the pTexture->imageData must be freed by the
caller.

\param pTexture
a pointer to Texture that will be filled out with texture information.

\param fileName
The TGA file to open.

\return
True if the file was open (you must delete pTexture->imageData), false
otherwise.
*/
/******************************************************************************/
int LoadTGA(M5Texture* pTexture, const char* fileName)
{
	/* Uncompressed TGA Header*/
	const GLubyte UNCOMPRESSED_TGA[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	/* Compressed TGA Header*/
	const GLubyte COMPRESSED_TGA[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	/*The first 18 bytes of the TGA header that I will read in*/
	M5TGAHeader tgaHeader;
	/*My file pointer*/
	FILE* pFile;

	/*Open the file*/
	fopen_s(&pFile, fileName, "rb");
	if (!pFile)
	{
		/*Make sure the file is opened*/
		const int SIZE = 512;
		char arr[SIZE];
		GetCurrentDirectory(SIZE, arr);
		std::string err("Could Not Load File: ");
		err += arr;
		err += "\\";
		err += fileName;
		M5DEBUG_ASSERT(pFile != 0, err.c_str());
		return false;
	}

	/*Read the first 18 bytes of the TGA Header file*/
	if (fread(&tgaHeader, sizeof(tgaHeader), 1, pFile) == 0)
	{
		LoadFail(0, &pFile, "Error Reading file");
		return false;
	}

	/*Fill in the texture data*/
	if (!UpdateTexture(pTexture, &tgaHeader))
	{
		LoadFail(0, &pFile, "Error reading file");
		return false;
	}

	/*Make sure the file is a power of two*/
	if (!M5Math::IsPowerOf2(pTexture->width) ||
		!M5Math::IsPowerOf2(pTexture->height))
	{
		LoadFail(pTexture, &pFile, "Textures must be powers of two.");
		return false;
	}

	/*Start File loading***************************************************/

	/*Compare with UMCOMPRESSED Header format*/
	if (!memcmp(UNCOMPRESSED_TGA, tgaHeader.headerPart1,
		sizeof(UNCOMPRESSED_TGA)))
	{
		/*If the 3rd byte is value 2, it is uncompressed, load that format*/
		LoadUncompressedTGA(pTexture, pFile);
	}
	else if (!memcmp(COMPRESSED_TGA, tgaHeader.headerPart1,
		sizeof(COMPRESSED_TGA)))
	{
		/*If the 3rd byte is 10, it is compressed, load that format*/
		LoadCompressedTGA(pTexture, pFile);
	}
	else /*The texture didn't match our types*/
	{
		/*Free texture data*/
		LoadFail(pTexture, &pFile, "Invalid File type");
		return false;
	}

	/*We are finished with the file.*/
	fclose(pFile);
	pFile = 0;
	return true;
}

}//end unnamed namespace

 /******************************************************************************/
 /*!
Destructor for ResourceManager class.  This checks to make sure all textures
have been unloaded.
 */
 /******************************************************************************/
M5ResourceManager::~M5ResourceManager(void)
{
	Clear();
}
/******************************************************************************/
/*!
Helper function to clear all textures in the texture map
*/
/******************************************************************************/
void M5ResourceManager::Clear(void)
{
	//Get itors to start and end
	M5TextureMapItor itor = m_textureMap.begin();
	M5TextureMapItor end = m_textureMap.end();

	while (itor != end)
	{
		glDeleteTextures(1, (GLuint*)&itor->second.id);
		++itor;
	}

	m_textureMap.clear();
}
/******************************************************************************/
/*!
The function to load a texture from a file.  This function will load 24 or 32
bit tga file only. (compressed or uncompressed).  This file will return
a unique id to the texture, so you can draw it later.  If the file can't
be loaded, it will return -1;

\attention
THIS FUNCTION ONLY LOADS 24 OR 32 BIT TGA FILES.  For every texture you
load, you must also call M5GraphicsUnloadTexture to unload it, when you are
done.

\param fileName
The name of the TGA file to load.

\return
A unique id for the texture.  Use the id to draw later. If if the function
returns -1, the texture was not loaded.
*/
/******************************************************************************/
int M5ResourceManager::LoadTexture(const char* fileName)
{
	//Check if we have already loaded the texture
	M5TextureMapItor itor = m_textureMap.find(fileName);
	if (itor != m_textureMap.end())
	{
		++(itor->second.count);
		return itor->second.id;
	}

	M5Texture texture;
	int id = -1;
	/*Try to load the data*/
	if (!LoadTGA(&texture, fileName))
		return id;

	/*Request a texture from openGL*/
	glGenTextures(1, (GLuint*)&id);
	/*Set up my texture*/
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.width, texture.height,
		0, texture.format, GL_UNSIGNED_BYTE, texture.imageData);

	/*Free texture data now*/
	delete[] texture.imageData;

	//Add LoadedTexture to texture map
	M5LoadedTexture loadedTex(fileName, id);
	m_textureMap.insert(std::make_pair(fileName, loadedTex));

	/*return given id.*/
	return id;
}
/******************************************************************************/
/*!
This function adds one to the given texture count.  This should be called if
The textureID is shared, for example in a clone function.

\param textureID
The ID to update

*/
/******************************************************************************/
void M5ResourceManager::UpdateTextureCount(int textureID)
{
	//Get itors to start and end
	M5TextureMapItor begin = m_textureMap.begin();
	M5TextureMapItor end = m_textureMap.end();

	//loop through and find the correct id
	for (; begin != end; ++begin)
	{
		if (begin->second.id == textureID)
		{
			++(begin->second.count);
			break;
		}
	}
}
/******************************************************************************/
/*!
This function returns the texture memory (allocated when you called
LoadTexture) back to the graphics card.  This must be called for every texture
you loaded.

\attention
You must unload every texture id that you loaded.

\param textureID
A valid textureID from LoadTexture
*/
/******************************************************************************/
void M5ResourceManager::UnloadTexture(int textureID)
{
	//Get itors to start and end
	M5TextureMapItor begin = m_textureMap.begin();
	M5TextureMapItor end = m_textureMap.end();

	//loop through and find the correct id
	for (; begin != end; ++begin)
	{
		if (begin->second.id == textureID)
		{
			//decrement id
			--(begin->second.count);
			//if that was the last load, delete the texture
			if (begin->second.count == 0)
			{
				m_textureMap.erase(begin);
				glDeleteTextures(1, (GLuint*)&textureID);
				break;
			}
		}
	}
}
/******************************************************************************/
/*!
Constructor for the M5LoadedTexture class.  This class is used to help store
the textures that have already been loaded.

\param str
The name of the texture that has been loaded.

\param newID
The id of the texture that is now loaded.
*/
/******************************************************************************/
M5ResourceManager::M5LoadedTexture::M5LoadedTexture(const std::string& str, int newID) :
	fileName(str), id(newID), count(1)
{
}