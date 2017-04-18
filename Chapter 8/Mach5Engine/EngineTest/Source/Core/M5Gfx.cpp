/******************************************************************************/
/*!
file    M5Gfx.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Singleton class to draw and modify the view of the screen
*/
/******************************************************************************/
#include "M5Gfx.h"
#include "M5Math.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5Debug.h"
#include "M5ResourceManager.h"
#include "GfxComponent.h"

#include <cmath> /*for tan*/
#include <cstring> /*memset*/
#include <string>
#include <vector>
#include <stack>

#include "windows.h"
#include "gl/glew.h"
#include "gl/gl.h"
#include "gl/glu.h"


namespace
{
/************************************************************************/
/* Defines for my Graphics Engine                                       */
/************************************************************************/
const GLdouble WIN_FOV = 90.0;           /*!< Field of view*/
const GLdouble START_CAM_DISTANCE = 60.0;/*!< Camera distance in the Z*/
const GLdouble CAM_NEAR_CLIP = 1.0;      /*!< Near clip plane in the Z*/
const GLdouble CAM_FAR_CLIP = 1000.0;    /*!< Far Clip plane in the Z*/
const GLdouble MIN_CAM_DISTANCE = 2.0f;  /*!< Min camera distance*/
const GLdouble MAX_CAM_DISTANCE = 999.0f;/*!< Max camera distance*/
/*Information about my font list*/
const int NUMBER_OF_CHARACTERS = 96;     /*!< The size*/
const int STARTING_CHARACTER = 32;       /*!< Start with the space*/

/************************************************************************/
/* Types used by my graphics Engine                                     */
/************************************************************************/

  //!A struct to hold my Vertex buffer object information
struct M5Mesh
{
	unsigned vertexCount; /*!< The number of vertices's in the list.*/
	GLuint   vboID;       /*!< The vbo id from openGl.*/
};

/*! A struct to define my vertex.*/
struct M5Vertex
{
	float x;/*The x position*/
	float y;/*The y position*/
	float z;/*The z position*/
	float tu;/*The u texture coord*/
	float tv;/*The v texture coord*/
};
struct GfxState
{
	GLdouble cameraZ; 
	GLdouble cameraX;
	GLdouble cameraY;    
	GLdouble cameraRot;
	int hudStart;
	int worldStart;
	int textureID;
	int height;
	float scaleX;
	float scaleY;
	float rot;
	float transX;
	float transY;
	float bgRed;
	float bgGreen;
	float bgBlue;
	unsigned char txRed;
	unsigned char txGreen;
	unsigned char txBlue;
	unsigned char txAlpha;
	

};

//!! A struct to hold and share data important to graphics functions.
GfxState s_gfxState;
std::stack<GfxState> s_pauseStack;

/*Projection data*/
GLdouble s_nearClip;      /*!< Near clip plane in the Z*/
GLdouble s_farClip;       /*!< Far Clip plane in the Z*/
GLdouble s_aspectRatio;   /*!< The aspect ration of the window. Width/Height*/
GLdouble s_fov;           /*!< Field of view*/
GLdouble s_persp[16];     /*!< A copy of the perspective matrix*/
GLdouble s_camera[16];    /*!< A copy of the camera matrix*/

/*Window drawing data*/
HGLRC    s_renderContext; /*!< The renderContext for OpenGL*/
HDC      s_deviceContext; /*!< The device context for windows*/
HWND     s_window;        /*!< The window for windows and openGL*/

/*Screen dimensions*/
int      s_width;         /*!< The width of the client area of the screen*/
int      s_height;        /*!< The height of the client area of the screen*/

/*Visible corners points of the world*/
M5Vec2   s_worldTopLeft;  /*!< The top left point on the screen.*/
M5Vec2   s_worldTopRight; /*!< The top right point on the screen.*/
M5Vec2   s_worldBotLeft;  /*!< The bottom Left point on the screen.*/
M5Vec2   s_worldBotRight; /*!< The bottom right point on the screen.*/

/*Font data*/
HFONT    s_font;          /*!< The font to create*/
HFONT    s_oldFont;       /*!< The old font*/
GLuint   s_fontBase;      /*!< My font list I will create*/

M5Mesh   s_mesh;          /*!< Quad Mesh since it is 2D game engine*/

//! Typedef for my vector of components
typedef std::vector<GfxComponent*> Components;

Components        s_worldComponents;
Components        s_hudComponents;
M5ResourceManager s_resourceManager;

/******************************************************************************/
/*!
Helper function to Set projection matrix is something needs to change.

\param [in] fov
The field of view for the height of the screen, specified in degrees.

\param [in] aspectRatio
The value of the width/height of the client area of the screen.

\param [in] nearClip
The distance of the near clip plane.

\param [in] farClip
The distance of the far clip plane.
*/
/******************************************************************************/
void SetPerspective(GLdouble fov, GLdouble aspectRatio, GLdouble nearClip, GLdouble farClip)
{
	//GLdouble modelView[16];
	/*Set our current view mode*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*Set up Perspective Matrix*/
	gluPerspective(fov, aspectRatio, nearClip, farClip);
	glGetDoublev(GL_PROJECTION_MATRIX, s_persp);

	/*Switch back to Model view*/
	glMatrixMode(GL_MODELVIEW);
}
}//end unnamed namespace

/******************************************************************************/
/*!
Set the Camera Matrix based on position of camera. The default x and y are 0.
The default z is 60.

\param [in] cameraX
This is the location of the camera and the target of the camera in the x.

\param [in] cameraY
This is the location of the camera and the target of the camera in the y.

\param [in] cameraZ
This is the height of the camera.

\param [in] cameraRot
This is the rotation in radians of the camera around the z axis.

*/
/******************************************************************************/
void M5Gfx::SetCamera(float cameraX, float cameraY,
	float cameraZ, float cameraRot)
{
	M5Mtx44 rotMatrix;
	cameraZ = M5Math::Clamp(cameraZ, static_cast<float>(MIN_CAM_DISTANCE),
		static_cast<float>(MAX_CAM_DISTANCE));
	s_gfxState.cameraX = cameraX;
	s_gfxState.cameraY = cameraY;
	s_gfxState.cameraZ = cameraZ;
	s_gfxState.cameraRot = cameraRot;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ,/*Camera position*/
		cameraX, cameraY, 0.0,    /*Target*/
		0, 1.0, 0.0);           /*UpVector*/

	rotMatrix.MakeRotateZ(cameraRot);
	glMultMatrixf((GLfloat*)&rotMatrix.m[0][0]);
	glGetDoublev(GL_MODELVIEW_MATRIX, s_camera);
	/*Re calculate world extents*/
	CalulateWorldExtents();
}


/******************************************************************************/
/*!
Initializes the Graphics Engine for drawing.  This will be called automatically
when the window is created.

\param [in] window
The window to draw to.

\param [in] width
The width of the client area of the window.

\param [in] height
The height of the client area of the window
*/
/******************************************************************************/
void M5Gfx::Init(HWND window, int width, int height)
{
	M5DEBUG_CALL_CHECK(1);

	/*Save the data for later use*/
	s_window = window;
	s_width = width;
	s_height = height;

	/*Set defaults for projection*/
	s_fov = WIN_FOV;
	s_nearClip = CAM_NEAR_CLIP;
	s_farClip = CAM_FAR_CLIP;
	s_aspectRatio = (GLdouble)width / height;

	/*Get Device context for window*/
	s_deviceContext = GetDC(s_window);

	/*This will assert if it fails otherwise gfxData.renderContext is valid*/
	RenderContextInit();
	FontInit();

	/*Give back the resource until we need it again.*/
	ReleaseDC(s_window, s_deviceContext);
	s_deviceContext = 0;

	/*Set fill mode*/
	glPolygonMode(GL_FRONT, GL_FILL);

	/*Enable Depth Test*/
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	/*Enable textures*/
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*Set up for position and color*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Set my GfxState
	/*Set my drawing viewPort*/
	SetViewport(0, 0, s_width, s_height);
	/*Set my camera*/
	SetCamera(0, 0, static_cast<float>(START_CAM_DISTANCE), 0);
	/*Set my projection matrix*/
	SetPerspective(s_fov, s_aspectRatio, s_nearClip, s_farClip);
	//Set up Texture
	SetTextureCoords();
	SetTextureColor();
	//Set Background Color
	SetBackgroundColor();
	s_gfxState.hudStart = 0;
	s_gfxState.worldStart = 0;

	/*Set up glew functions*/
	glewInit();
	VertexBufferInit();
}
/******************************************************************************/
/*!
Closes all resources associated with the Graphics Engine.
*/
/******************************************************************************/
void M5Gfx::Shutdown(void)
{
	M5DEBUG_CALL_CHECK(1);

	M5DEBUG_ASSERT(s_hudComponents.size() == 0 && s_worldComponents.size() == 0,
		"Some Components were not unloaded.");

	s_hudComponents.clear();
	s_worldComponents.clear();
	s_resourceManager.Clear();

	glDeleteBuffers((GLsizei)1, &s_mesh.vboID);
	glDeleteLists(s_fontBase, NUMBER_OF_CHARACTERS);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(s_renderContext);
	s_renderContext = 0;
}
/******************************************************************************/
/*!
Sets the beginning of a draw frame.  This must be called before trying to draw
anything.

\attention
This must be called before drawing anything.

*/
/******************************************************************************/
void M5Gfx::StartScene(void)
{
	s_deviceContext = GetDC(s_window);
	wglMakeCurrent(s_deviceContext, s_renderContext);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
/******************************************************************************/
/*!
Specifies when the draw frame is finished.  This must be called after all draw
calls.

\attention
This must be called after all draw calls.

*/
/******************************************************************************/
void M5Gfx::EndScene(void)
{
	SwapBuffers(s_deviceContext);
	ReleaseDC(s_window, s_deviceContext);
	s_deviceContext = 0;
}
/******************************************************************************/
/*!
Writes Text to the screen. Using an internal font.  This is best used for debug
text. (It is better to use images for the text you want.)

\attention
This is best used for debug only.

\param [in] text
The Text you want to draw to the screen.

\param [in] x
The x location to start.

\param [in] y
The y location to start.
*/
/******************************************************************************/
void M5Gfx::WriteText(const char* text, float x, float y)
{
	/*Disable textures*/
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	/*Set up Matrix*/
	glPushMatrix();
	glRasterPos2f(x, y);

	/*Set up display list*/
	glPushAttrib(GL_LIST_BIT);
	glListBase(s_fontBase - STARTING_CHARACTER);

	/*Draw text display list*/
	glCallLists(static_cast<GLsizei>(std::strlen(text)), GL_UNSIGNED_BYTE, text);

	/*restore display list and matrix*/
	glPopAttrib();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
/******************************************************************************/
/*!
Draws the currently set texture at this location, scale and rotation.

\param [in] worldMatrix
The world matrix that will define the scale rotation and translation.
*/
/******************************************************************************/
void M5Gfx::Draw(const M5Mtx44& worldMatrix)
{
	/*Set the matrix mode*/
	glMatrixMode(GL_MODELVIEW);
	/*Add this matrix to the view*/
	glPushMatrix();
	/*Right now my matrix is the transpose of open gl*/
	glMultMatrixf(reinterpret_cast<const GLfloat*>(&worldMatrix.m[0][0]));

	/*Set the start of my position data*/
	glVertexPointer(3, GL_FLOAT, sizeof(M5Vertex), 0);
	/*Set  my texture positions*/
	glTexCoordPointer(2, GL_FLOAT, sizeof(M5Vertex),
		((char*)0 + sizeof(float) * 3));

	/*Draw my object*/
	glDrawArrays(GL_TRIANGLES, 0, s_mesh.vertexCount);

	/*Remove this matrix*/
	glPopMatrix();
}
/******************************************************************************/
/*!
Sets the current texture to draw.

\attention
The texture ID should be one that was returned from Loading a texture.

\param [in] textureID
The texture id to set.
*/
/******************************************************************************/
void M5Gfx::SetTexture(int textureID)
{
	s_gfxState.textureID = textureID;
	glBindTexture(GL_TEXTURE_2D, textureID);
}
/******************************************************************************/
/*!
Set the Resolution for the game.

\param [in] width
The new width of the game.

\param [in] height
The new height of the game.
*/
/******************************************************************************/
void M5Gfx::SetResolution(int width, int height)
{
	s_width = width;
	s_height = height;
	s_aspectRatio = static_cast<GLdouble>(width) / height;
	//SetPerspective(s_fov, s_aspectRatio, s_nearClip, s_farClip);
	SetViewport(0, 0, width, height);

	/*update world extents*/
	CalulateWorldExtents();
}
/******************************************************************************/
/*!
Uses a 4x4 matrix to set the texture coordinates for the current texture.
Texture coordinates are default to (0, 0) in the lower left corner and (1,1) in
the upper right corner.

\param [in] scaleX
The amount to scale in the x direction.

\param [in] scaleY
The amount to scale in the y direction.

\param [in] radians
The amount to rotate the texture.

\param [in] transX
The amount to translate in the x direction.

\param [in] transY
The amount to translate in the y direction.
*/
/******************************************************************************/
void M5Gfx::SetTextureCoords(float scaleX, float scaleY, float radians, float transX, float transY)
{
	M5Mtx44 transform;
	transform.MakeTransform(scaleX, scaleY, radians, transX, transY, 0.f);
	glMatrixMode(GL_TEXTURE);
	glLoadMatrixf(&transform.m[0][0]);
	glMatrixMode(GL_MODELVIEW);
	//save state
	s_gfxState.scaleX = scaleX;
	s_gfxState.scaleY = scaleY;
	s_gfxState.rot = radians;
	s_gfxState.transX = transX;
	s_gfxState.transY = transY;
}
/******************************************************************************/
/*!
Set the color of the back ground screen. These floats must be between 0 and 1.

\param [in] red
The amount of the red in the background.  The default is 0.

\param [in] blue
The amount of blue in the background.  The default is 0.

\param [in] green
The amount of green in the background.  The default is 0.
*/
/******************************************************************************/
void M5Gfx::SetBackgroundColor(float red, float green, float blue)
{
	s_gfxState.bgRed = red;
	s_gfxState.bgGreen = green;
	s_gfxState.bgBlue = blue;
	glClearColor(red, green, blue, 1.0);
}
/******************************************************************************/
/*!
Gets the top left point on the screen in world coordinates.

\param [out] outVec
Gets the top left point on the screen in world coordinates.
*/
/******************************************************************************/
void M5Gfx::GetWorldTopLeft(M5Vec2& outVec)
{
	outVec = s_worldTopLeft;
}
/******************************************************************************/
/*!
Gets the top right point on the screen.

\param [out] outVec
Gets the top right point on the screen.
*/
/******************************************************************************/
void M5Gfx::GetWorldTopRight(M5Vec2& outVec)
{
	outVec = s_worldTopRight;
}
/******************************************************************************/
/*!
Gets the bottom left point on the screen in world coordinates.

\param outVec
Gets the bottom left point on the screen in world coordinates.
*/
/******************************************************************************/
void M5Gfx::GetWorldBotLeft(M5Vec2& outVec)
{
	outVec = s_worldBotLeft;
}
/******************************************************************************/
/*!
Gets the bottom right point on the screen in world coordinates.

\param [out] outVec
Gets the bottom right point on the screen in world coordinates.
*/
/******************************************************************************/
void M5Gfx::GetWorldBotRight(M5Vec2& outVec)
{
	outVec = s_worldBotRight;
}
/******************************************************************************/
/*!
Sets the color to add to the texture color.  This can be used to change color
of a texture so you don't need two textures.

/attention
This will also change the color of WriteText

\param [in] color
The color to set.  The color is specified as ABGR, where the most significant
byte of the int is Alpha.

*/
/******************************************************************************/
void M5Gfx::SetTextureColor(unsigned color)
{
	const GLubyte* pColor = reinterpret_cast<const GLubyte*>(&color);
	s_gfxState.txRed = pColor[0];
	s_gfxState.txGreen = pColor[1];
	s_gfxState.txBlue = pColor[2];
	s_gfxState.txAlpha = pColor[3];

	glColor4ubv(pColor);
}
/******************************************************************************/
/*!
Sets the color to add to the texture color.  This can be used to change color
of a texture so you don't need two textures.

/attention
This will also change the color of DrawText

\param [in] alpha
The amount you can see the image.  0 is invisable.

\param [in] blue
The amount of blue that texture has.

\param [in] green
The amount of green that texture has.

\param [in] red
The amount of red that texture has.

*/
/******************************************************************************/
void M5Gfx::SetTextureColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	unsigned char color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	s_gfxState.txRed = color[0];
	s_gfxState.txGreen = color[1];
	s_gfxState.txBlue = color[2];
	s_gfxState.txAlpha = color[3];

	glColor4ubv(color);
}
/******************************************************************************/
/*!
This function takes two float pointers with values in screen space and
converts them to values in world space.

\attention
This function will modify the input values.

\param [in,out] x
A pointer to a float in screen space that will be changed to world space.

\param [in,out] y
A pointer to a float in screen space that will be changed to world space.

*/
/******************************************************************************/
void M5Gfx::ConvertScreenToWorld(float& x, float& y)
{
	GLint viewPort[4];
	GLdouble winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetIntegerv(GL_VIEWPORT, viewPort);

	/*Get my window z by projecting world space 0*/
	gluProject(0, 0, 0, s_camera, s_persp, viewPort, &winX, &winY, &winZ);

	/*Get my window x and y*/
	winX = x;
	winY = y;

	/*now figure out what the world location is*/
	gluUnProject(winX, winY, winZ, s_camera, s_persp, viewPort, &posX, &posY, &posZ);

	x = static_cast<float>(posX);
	y = static_cast<float>(posY);
}
/******************************************************************************/
/*!
This function takes two float pointers with values in world space and
converts them to values in screen space.

\attention
This function will modify the input values.

\param [in,out] x
A pointer to a float in world space that will be changed to screen space.

\param [in,out] y
A pointer to a float in world space that will be changed to screen space.

*/
/******************************************************************************/
void M5Gfx::ConvertWorldToScreen(float& x, float& y)
{
	GLint viewPort[4];
	GLdouble winX, winY, winZ;

	glGetIntegerv(GL_VIEWPORT, viewPort);
	gluProject(x, y, 0, s_camera, s_persp, viewPort, &winX, &winY, &winZ);

	x = static_cast<float>(winX);
	y = static_cast<float>(winY);
}
/******************************************************************************/
/*!
This mode sets the scene to use the perspective matrix.  This is the standard
mode to draw objects in.  Z order is important and changing the distance
of the camera effects object size.  The draw location must be in world
coordinates.
*/
/******************************************************************************/
void M5Gfx::SetToPerspective(void)
{
	SetPerspective(s_fov, s_aspectRatio, s_nearClip, s_farClip);
	SetCamera(static_cast<float>(s_gfxState.cameraX),
		static_cast<float>(s_gfxState.cameraY),
		static_cast<float>(s_gfxState.cameraZ),
		static_cast<float>(s_gfxState.cameraRot));
}
/******************************************************************************/
/*!
This mode is used to HUD objects.  Z order is still effective, but distance
from the camera is not.  The draw location must be in screen coordinates.

\attention
You should not set camera position while this mode is active.
*/
/******************************************************************************/
void M5Gfx::SetToOrtho(void)
{
	/*glDisable(GL_DEPTH_TEST);*/
	/*Set our current view mode*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*Set up Perspective Matrix*/
	/*glOrtho(0, gfxData.width, gfxData.height, 0, -1.0f, 1.0f);*/
	gluOrtho2D(0, s_width, 0, s_height);
	/*Switch back to Model view*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/******************************************************************************/
/*!
Lets the user set the drawing view port in screen space.

\param [in] xStart
The new staring location of the viewport in screen space.

\param [in] yStart
The new starting location of the viewport in screen space.

\param [in] width
The new width of the viewport in pixels.

\param [in] height
The new height of the viewport in pixels
*/
/******************************************************************************/
void M5Gfx::SetViewport(int xStart, int yStart, int width, int height)
{
	glViewport(xStart, yStart, width, height);
}
/******************************************************************************/
/*!
Calculates the corner positions of the world that will be shown on screen.
*/
/******************************************************************************/
void M5Gfx::CalulateWorldExtents(void)
{
	float worldMaxY;
	float worldMaxX;
	float worldMinY;
	float worldMinX;
	M5Mtx44 rotMatrix;

	rotMatrix.MakeRotateZ(static_cast<float>(-s_gfxState.cameraRot));

	/*Calculate world corners based on camera z*/
	float angle = M5Math::DegreeToRadian(static_cast<float>(.5f * s_fov));

	worldMaxY = std::tan(angle) * static_cast<float>(s_gfxState.cameraZ);
	worldMaxX = worldMaxY * static_cast<float>(s_aspectRatio);
	worldMinY = -worldMaxY;
	worldMinX = -worldMaxX;

	/*Shift the corners based on the camera x and y*/
	worldMaxY += static_cast<float>(s_gfxState.cameraY);
	worldMinY += static_cast<float>(s_gfxState.cameraY);
	worldMaxX += static_cast<float>(s_gfxState.cameraX);
	worldMinX += static_cast<float>(s_gfxState.cameraX);

	/*then rotate the corner points*/
	s_worldTopLeft.x = worldMinX*rotMatrix.m[0][0] + worldMaxY*rotMatrix.m[1][0];
	s_worldTopLeft.y = worldMinX*rotMatrix.m[0][1] + worldMaxY*rotMatrix.m[1][1];

	s_worldTopRight.x = worldMaxX*rotMatrix.m[0][0] + worldMaxY*rotMatrix.m[1][0];
	s_worldTopRight.y = worldMaxX*rotMatrix.m[0][1] + worldMaxY*rotMatrix.m[1][1];

	s_worldBotLeft.x = worldMinX*rotMatrix.m[0][0] + worldMinY*rotMatrix.m[1][0];
	s_worldBotLeft.y = worldMinX*rotMatrix.m[0][1] + worldMinY*rotMatrix.m[1][1];

	s_worldBotRight.x = worldMaxX*rotMatrix.m[0][0] + worldMinY*rotMatrix.m[1][0];
	s_worldBotRight.y = worldMaxX*rotMatrix.m[0][1] + worldMinY*rotMatrix.m[1][1];
}

/******************************************************************************/
/*!
Helper function to create a font for debug text drawing to the screen.
*/
/******************************************************************************/
void M5Gfx::FontInit(void)
{
	const float FONT_HEIGHT_SCALE = .03f;
	/*Get a list of bitmaps from openGl*/
	s_fontBase = glGenLists(NUMBER_OF_CHARACTERS);

	/*Create my windows font*/
	s_font = CreateFont(
		(int)(s_height * FONT_HEIGHT_SCALE),/*Height*/ //TODO: Make this const
		0,                     /*width*/
		0,                     /*angle of escapement*/
		0,                     /*orientation,*/
		400,                   /*font weight*/
		FALSE,                 /*Italic*/
		FALSE,                 /*Underlined*/
		FALSE,                 /*Strike out*/
		DEFAULT_CHARSET,       /*Char set identifier*/
		OUT_TT_PRECIS,         /*Output Precision*/
		CLIP_DEFAULT_PRECIS,   /*Clipping Precision*/
		ANTIALIASED_QUALITY,   /*OutputQuality*/
		DEFAULT_PITCH,         /*Family and Pitch*/
		"Terminal");           /*Font name*/

							   /*Switch to my created font*/
	s_oldFont = (HFONT)SelectObject(s_deviceContext, s_font);

	/*Tell open gl about my font*/
	wglUseFontBitmaps(s_deviceContext, STARTING_CHARACTER, NUMBER_OF_CHARACTERS, s_fontBase);
	/*Set back to original font*/
	SelectObject(s_deviceContext, s_oldFont);
	/*Deleted my created font.*/
	DeleteObject(s_font);

}
/******************************************************************************/
/*!
Creates the single vertex buffer in the game.  Since this is currently only a
2D game engine it only needs a Quad.

My verts are like this

2--------(1,6)
|           |
|           |
|           |
|           |
(3,4)----- 5
*/
/******************************************************************************/
void M5Gfx::VertexBufferInit(void)
{
	const int VERT_COUNT = 6;
	/*Hard code my verts, because we are only supporting one vbo*/
	M5Vertex vertArray[6] = {
	  { .5f, .5f, 0.f, 1.f, 1.f }, /*1*/
	  { -.5f, .5f, 0.f, 0.f, 1.f }, /*2*/
	  { -.5f, -.5f, 0.f, 0.f, 0.f }, /*3*/

	  { -.5f, -.5f, 0.f, 0.f, 0.f }, /*4*/
	  { .5f, -.5f, 0.f, 1.f, 0.f }, /*5*/
	  { .5f, .5f, 0.f, 1.f, 1.f } }; /*6*/
	GLsizei dataSize = sizeof(M5Vertex) * VERT_COUNT;

	/*Generate my vbo*/
	glGenBuffers((GLsizei)1, &s_mesh.vboID);
	s_mesh.vertexCount = VERT_COUNT;

	/*Set my buffer to the current*/
	glBindBuffer(GL_ARRAY_BUFFER, s_mesh.vboID);
	/*Fill in data into my vbo*/
	glBufferData(GL_ARRAY_BUFFER, dataSize, vertArray, GL_STATIC_DRAW);
}
/******************************************************************************/
/*!
This function will initialize the render context.  If it fails the program will
assert in debug or crash in release mode.  After calling this the
renderContext will be valid.
*/
/******************************************************************************/
void M5Gfx::RenderContextInit(void)
{
	/*A struct the specifies information about the back buffer*/
	PIXELFORMATDESCRIPTOR pfd;
	int pixelFormat; /*The result value after choosing my pixel format*/
	BOOL result; /*Used to check for errors.*/

				 /*Clear my pfd and only set the values I need.*/
	std::memset(&pfd, 0, sizeof(pfd));

	/*Set up information about pixels for buffer and back buffer*/
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	/*A set of flags that specify the properties of the pixel buffer*/
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;

	/*Choose back buffer information*/
	pixelFormat = ChoosePixelFormat(s_deviceContext, &pfd);
	M5DEBUG_ASSERT(pixelFormat != 0, "Unable to chose PixelFormat. Your video card is out of date");

	/*Set back buffer information*/
	result = SetPixelFormat(s_deviceContext, pixelFormat, &pfd);
	M5DEBUG_ASSERT(result != 0, "Unable to Set PixelFormat. Your video card is out of date");

	/*Create openGL render context*/
	s_renderContext = wglCreateContext(s_deviceContext);
	M5DEBUG_ASSERT(s_renderContext != 0, "Unable to Create Render Context. Your video card is out of date");

	/*Set the openGl render context*/
	result = wglMakeCurrent(s_deviceContext, s_renderContext);
	M5DEBUG_ASSERT(result != 0, "Unable to Set Render Context. Your video card is out of date");
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
int M5Gfx::LoadTexture(const char* fileName)
{
	M5DEBUG_ASSERT(fileName != 0, "Filename is NULL");
	return s_resourceManager.LoadTexture(fileName);
}
/******************************************************************************/
/*!
This function adds one to the given texture count.  This should be called if
The textureID is shared, for example in a clone function.

\param textureID
The ID to update

*/
/******************************************************************************/
void M5Gfx::UpdateTextureCount(int textureID)
{
	s_resourceManager.UpdateTextureCount(textureID);
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
void M5Gfx::UnloadTexture(int textureID)
{
	s_resourceManager.UnloadTexture(textureID);
}
/******************************************************************************/
/*!
Adds the given GfxComponent to the list of world object.

\param pGfxComp
The Component to register.
*/
/******************************************************************************/
void M5Gfx::RegisterWorldComponent(GfxComponent* pGfxComp)
{
	s_worldComponents.push_back(pGfxComp);
}
/******************************************************************************/
/*!
Adds the given GfxComponent to the list of HUD objects.

\param pGfxComp
The Component to register.
*/
/******************************************************************************/
void M5Gfx::RegisterHudComponent(GfxComponent* pGfxComp)
{
	s_hudComponents.push_back(pGfxComp);
}
/******************************************************************************/
/*!
Seaches the HUD and World Lists and removes the given component from both.

\param pGfxComp
The Component to unregister.
*/
/******************************************************************************/
void M5Gfx::UnregisterComponent(GfxComponent* pGfxComp)
{
	//Unregister from world list if it exists there
	for (size_t i = s_gfxState.worldStart; i < s_worldComponents.size(); ++i)
	{
		if (s_worldComponents[i] == pGfxComp)
		{
			s_worldComponents[i] = s_worldComponents[s_worldComponents.size() - 1];
			s_worldComponents.pop_back();
		}
	}
	//Unregister from hud list if it exists there
	for (size_t i = s_gfxState.hudStart; i < s_hudComponents.size(); ++i)
	{
		if (s_hudComponents[i] == pGfxComp)
		{
			s_hudComponents[i] = s_hudComponents[s_hudComponents.size() - 1];
			s_hudComponents.pop_back();
		}
	}
}
/******************************************************************************/
/*!
Draws all registered components

*/
/******************************************************************************/
void M5Gfx::Update(void)
{
	size_t size = s_worldComponents.size();
	StartScene();

	SetToPerspective();
	for (size_t i = s_gfxState.worldStart; i < size; ++i)
		s_worldComponents[i]->Draw();

	SetToOrtho();
	size = s_hudComponents.size();
	for (size_t i = s_gfxState.hudStart; i < size; ++i)
		s_hudComponents[i]->Draw();

	EndScene();
}
/******************************************************************************/
/*!
Pauses the graphics engine and saves the state of all user modifiable variables.

\param drawPaused
True if we want to draw the paused objects.  False otherwise
*/
/******************************************************************************/
void M5Gfx::Pause(bool drawPaused /*= false*/)
{
	s_pauseStack.push(s_gfxState);
	if (!drawPaused)
	{
		s_gfxState.worldStart = s_worldComponents.size();
		s_gfxState.hudStart = s_hudComponents.size();
	}
}
/******************************************************************************/
/*!
Resumes the Previusly saved state of the graphics engine.
*/
/******************************************************************************/
void M5Gfx::Resume(void)
{
	s_gfxState = s_pauseStack.top();
	SetCamera(static_cast<float>(s_gfxState.cameraX), 
		static_cast<float>(s_gfxState.cameraY),
		static_cast<float>(s_gfxState.cameraZ),
		static_cast<float>(s_gfxState.cameraRot));
	SetBackgroundColor(s_gfxState.bgRed, s_gfxState.bgGreen, s_gfxState.bgBlue);
	SetTexture(s_gfxState.textureID);
	SetTextureCoords(s_gfxState.scaleX, s_gfxState.scaleY, s_gfxState.rot, s_gfxState.transX, s_gfxState.transY);
	SetTextureColor(s_gfxState.txRed, s_gfxState.txGreen, s_gfxState.txBlue, s_gfxState.txAlpha);
}


