/******************************************************************************/
/*!
\file   M5Gfx.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Singleton class to draw and modify the view of the screen
*/
/******************************************************************************/
#ifndef M5_GRAPHICS_H
#define M5_GRAPHICS_H

/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

//Forward declarations
struct M5Vec2;
struct M5Mtx44;
class  GfxComponent;


//! Singleton class to draw and modify the view of the screen
class M5Gfx
{
public:
	friend class M5App;
	friend class M5StageManager;

	
	/*Use this to load a texture from file*/
	static int LoadTexture(const char* fileName);
	/*You must unload every texture that you load*/
	static void UnloadTexture(int textureID);
	/*Sets the position of the camera in perspective mode.  There is no camera in ortho mode.*/
	static void SetCamera(float cameraX, float cameraY, float cameraZ, float cameraRot);
	/*Changes the background color*/
	static void SetBackgroundColor(float red, float green, float blue);
	/*Draws the selected texture based on the matrix*/
	static void Draw(const M5Mtx44& worldMatrix);
	/*Writes text on the screen*/
	static void WriteText(const char* text, float x, float y);
	/*Use this to select the texture that you want to draw*/
	static void SetTexture(int textureID);
	/*This is used to scale, rotate, or translate a texture. It is best used for frame animation*/
	static void SetTextureCoords(float scaleX, float scaleY, float radians, float transX, float transY);
	/*Blends the given color with the texture*/
	static void SetTextureColor(unsigned color);
	/*Blends the given color with the texture*/
	static void SetTextureColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	/*Converts a point in screen space (mouse click) to the correct position in the world*/
	static void ConvertScreenToWorld(float& x, float& y);
	/*Converts a position in the world into screen space*/
	static void ConvertWorldToScreen(float& x, float& y);
	/*Set where on the the window to draw*/
	static void SetViewport(int xStart, int yStart, int width, int height);
	/*Gets the Top Left corner of the world*/
	static void GetWorldTopLeft(M5Vec2& outParam);
	/*Gets the Top right corner of the world*/
	static void GetWorldTopRight(M5Vec2& outParam);
	/*Gets the Bottom left corner of the world*/
	static void GetWorldBotLeft(M5Vec2& outParam);
	/*Gets the Bottom Right corner of the world*/
	static void GetWorldBotRight(M5Vec2& outParam);
	static void RegisterWorldComponent(GfxComponent* pGfxComp);
	static void RegisterHudComponent(GfxComponent* pGfxComp);
	static void UnregisterComponent(GfxComponent* pGfxComp);
private:
	/*This should be called once before drawing all objects*/
	static void StartScene(void);
	/*This should be called once after drawing all objects*/
	static void EndScene(void);
	/*Use this to draw game objects.  Z order and distance from the camera effects the size*/
	static void SetToPerspective(void);
	/*Use this to draw HUD objects. Distance from the camara doesn't  effect the object*/
	static void SetToOrtho(void);
	static void Update(void);
	static void SetResolution(int width, int height);
	static void CalulateWorldExtents(void);
	static void FontInit(void);
	static void VertexBufferInit(void);
	static void Init(HWND window, int width, int height);
	static void Shutdown(void);
	static void RenderContextInit(void);
};//end M5Gfx




#endif