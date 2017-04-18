/******************************************************************************/
/*!
file    M5App.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/6

A globably accessable Static class for Creating and controlling the window in
the Mach 5 Engine.
*/
/******************************************************************************/
#include "M5App.h"
#include "M5Debug.h"
#include "M5Vec2.h"
#include "M5StageManager.h"
#include "M5ObjectManager.h"
#include "M5Input.h"
#include "M5Timer.h"
#include "M5Gfx.h"
#include "Windowsx.h" /*For GET_X_LPARAM, GET_Y_LPARAM*/


namespace
{
/*The name of the Windows class. It is used to register and create the window*/
const char* CLASS_NAME = "Mach5Class";
/*My Window style if the user chooses full screen*/
const DWORD FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
/*My Window style if the user chooses windowed mode.*/
const DWORD WINDOWED_STYLE = WS_POPUP | WS_CAPTION;

//"Private" class data
const char* s_title;       /*!<The title of the window */
HINSTANCE   s_instance;    /*!< The instance from WinMain*/
WNDCLASS    s_winClass;    /*!< The window class for creating the window*/
HWND        s_window;      /*!< The window after creating it*/
DWORD       s_style;       /*!< The windows style */
bool        s_isQuitting;  /*!< The quit stage of the game*/
bool        s_isFullScreen;/*!< If the window is in full screen or not*/
int         s_height;      /*!< The height of the client area of the window */
int         s_width;       /*!< The width of the client area of the window */

/******************************************************************************/
/*!
This function translates a windows key code into a Mach5 Engine Key code.  This
way, the game doesn't care about windows key codes.

\param [in] wp
The WParam of the windows message.  This contains the windows key code.

\return
The Key code to return.

*/
/******************************************************************************/
M5KeyCode TranslateKey(WPARAM wp)
{
  switch (wp)
  {
  case VK_RETURN:  return M5_RETURN;
  case VK_SPACE:   return M5_SPACE;
  case VK_UP:      return M5_ARROW_UP;
  case VK_DOWN:    return M5_ARROW_DOWN;
  case VK_RIGHT:   return M5_ARROW_RIGHT;
  case VK_LEFT:    return M5_ARROW_LEFT;
  case VK_TAB:     return M5_TAB;
  case VK_SHIFT:   return M5_SHIFT;
  case VK_CONTROL: return M5_CONTROL;
  case VK_ESCAPE:  return M5_ESCAPE;
  case VK_BACK:    return M5_BACKSPACE;
  case 'A':        return M5_A;
  case 'B':        return M5_B;
  case 'C':        return M5_C;
  case 'D':        return M5_D;
  case 'E':        return M5_E;
  case 'F':        return M5_F;
  case 'G':        return M5_G;
  case 'H':        return M5_H;
  case 'I':        return M5_I;
  case 'J':        return M5_J;
  case 'K':        return M5_K;
  case 'L':        return M5_L;
  case 'M':        return M5_M;
  case 'N':        return M5_N;
  case 'O':        return M5_O;
  case 'P':        return M5_P;
  case 'Q':        return M5_Q;
  case 'R':        return M5_R;
  case 'S':        return M5_S;
  case 'T':        return M5_T;
  case 'U':        return M5_U;
  case 'V':        return M5_V;
  case 'W':        return M5_W;
  case 'X':        return M5_X;
  case 'Y':        return M5_Y;
  case 'Z':        return M5_Z;
  case '0':        return M5_0;
  case '1':        return M5_1;
  case '2':        return M5_2;
  case '3':        return M5_3;
  case '4':        return M5_4;
  case '5':        return M5_5;
  case '6':        return M5_6;
  case '7':        return M5_7;
  case '8':        return M5_8;
  case '9':        return M5_9;
  case VK_F1:      return M5_F1;
  case VK_F2:      return M5_F2;
  case VK_F3:      return M5_F3;
  case VK_F4:      return M5_F4;
  case VK_F5:      return M5_F5;
  case VK_F6:      return M5_F6;
  case VK_F7:      return M5_F7;
  case VK_F8:      return M5_F8;
  case VK_F9:      return M5_F9;
  case VK_F10:     return M5_F10;
  case VK_F11:     return M5_F11;
  case VK_F12:     return M5_F12;
  case VK_LSHIFT:  return M5_SHIFT_LEFT;
  case VK_RSHIFT:  return M5_SHIFT_RIGHT;
  case VK_LCONTROL:return M5_CONTROL_LEFT;
  case VK_RCONTROL:return M5_CONTROL_RIGHT;

  default:        return M5_INVALID;
  }
}
/******************************************************************************/
/*!
Makes the client area my desired size, and centers the window on screen. This
function should not be called by students.

\param [in]style
The style of my window

\param [in, out]size
This holds the size of my desired client area, and will by changed to the
size I should request from create window.

\param [out]xStart
This will be filled in the the start location in the x;

\param [out]yStart
This will be filled in the the start location in the y;
*/
/******************************************************************************/
void M5AdjustAndCenterWindow(DWORD style, RECT& size, int& xStart, int& yStart)
{
  DEVMODE dm = { 0 };
  int winWidth, winHeight;

  /*Get the size of the screen*/
  dm.dmSize = sizeof(dm);
  EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);

  /*Make client area of window the correct size */
  AdjustWindowRect(&size, style, 0);

  /*Calculate new width and height */
  winWidth = size.right - size.left;
  winHeight = size.bottom - size.top;

  /* Get start position for center */
  xStart = (int)((dm.dmPelsWidth / 2) - (winWidth / 2));
  yStart = (int)((dm.dmPelsHeight / 2) - (winHeight / 2));
}

}//end unnamed namespace

/******************************************************************************/
/*!
Gets Messages from windows and passes them to the WinProc.
*/
/******************************************************************************/
void M5App::ProcessMessages(void)
{
  MSG msg;
  while (PeekMessage(&msg, s_window, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}
/******************************************************************************/
/*!
Change the application between fullscreen mode and windowed mode

\param [in] fullScreen
The new state of the window.
*/
/******************************************************************************/
void M5App::SetFullScreen(bool fullScreen)
{
  /*Create variables to adjust window size and start position*/
  RECT rect = { 0 };
  int xStart = 0, yStart = 0;
  rect.right = s_width;
  rect.bottom = s_height;

  s_isFullScreen = fullScreen;

  /*Check if we are going into full screen or not*/
  if (fullScreen)
  {
    /*Get the current display settings*/
    DEVMODE dmScreenSettings;
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);

    /*Change the resolution to the resolution of my window*/
    dmScreenSettings.dmPelsWidth = (DWORD)s_width;
    dmScreenSettings.dmPelsHeight = (DWORD)s_height;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    /*Make sure my window style is full screen*/
    s_style = FULLSCREEN_STYLE;

    /*Check if it worked.  If it didn't set to window mode.*/
    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      s_isFullScreen = false;
      s_style = WINDOWED_STYLE;
      ChangeDisplaySettings(NULL, 0);/*If So Switch Back To The Desktop*/
      M5Debug::MessagePopup("FullScreen is not supported. "
        "You are being switched to Windowed Mode");
    }
  }
  else
  {
    ChangeDisplaySettings(NULL, 0);/*If So Switch Back To The Desktop*/
    /*Make sure I am in windows style*/
    s_style = WINDOWED_STYLE;
  }

  /*This will change my windows style*/
  SetWindowLong(s_window, GWL_STYLE, s_style);
  /*This will make window the correct size and find the start position*/
  M5AdjustAndCenterWindow(s_style, rect, xStart, yStart);
  /*This changes my window size and start position*/
  MoveWindow(s_window, xStart, yStart, rect.right - rect.left, rect.bottom - rect.top, TRUE);
  /*This is required after SetWindowLong*/
  ::ShowWindow(s_window, SW_SHOWNORMAL);
  /*This sets my window to the front.*/
  SetForegroundWindow(s_window);

}
/******************************************************************************/
/*!
Initializes the Application.  This should be called first before doing
anything else.

\param [in] initData
A pointer to information about how to create the window.

\attention
You MUST call this FIRST before update or shutdown when creating a game.

*/
/******************************************************************************/
void M5App::Init(const M5InitData& initData)
{
  //Make sure this function is called only 1 time.
  M5DEBUG_CALL_CHECK(1);

  /*Set up s_appData*/
  s_isQuitting = false;
  s_height = initData.height;
  s_width = initData.width;

  /*Set up window data*/
  s_title = initData.title;
  s_instance = initData.instance;
  s_isFullScreen = initData.fullScreen;
  s_style = WINDOWED_STYLE;

  /*Use default for my WNDCLASS*/
  s_winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  s_winClass.cbClsExtra = 0;
  s_winClass.cbWndExtra = 0;
  s_winClass.hInstance = initData.instance; /*This is the instance from WinMain*/
  s_winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  s_winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  s_winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  s_winClass.lpszMenuName = NULL;
  s_winClass.lpszClassName = CLASS_NAME;
  s_winClass.lpfnWndProc = M5WinProc;/*This is my winproc function*/

  /*First register class */
  RegisterClass(&s_winClass);

  int xStart = 0, yStart = 0;
  RECT size = { 0, 0, 0, 0 };
  /*Set up suggested window size*/
  size.right = initData.width;
  size.bottom = initData.height;
  M5AdjustAndCenterWindow(s_style, size, xStart, yStart);

  /*Call create window*/
  s_window = CreateWindow(
    CLASS_NAME,             /*Class name*/
    initData.title,       /*Window Title*/
    s_style,                /*Window Style*/
    xStart,                 /*X Starting pos*/
    yStart,                 /*Y Starting Pos*/
    size.right - size.left, /*Width*/
    size.bottom - size.top, /*Height*/
    0,                      /*Parent Window*/
    0,                      /*Menu*/
    initData.instance,    /*HInstance*/
    0                       /*Lparam This will be available in WM_CREATE*/
  );

  if (s_isFullScreen)
  {
    s_style = FULLSCREEN_STYLE;
    SetFullScreen(true);
  }

  /*Make sure window is visible and the correct messages are being sent.*/
  ::ShowWindow(s_window, SW_SHOWNORMAL);
  ::UpdateWindow(s_window);//call the 

  
  M5StageManager::Init(*initData.pGData, initData.fps);
  M5ObjectManager::Init();
  M5Input::Init();
}
/******************************************************************************/
/*!
Updates the game stages based on what the user passed in.  This should be
called once after M5Application::Init and after the user has added game stages
and start stage.

\attention
Add game stages and start stage before calling this function
*/
/******************************************************************************/
void M5App::Update(void)
{
  /*Loop until the application needs to quit.*/
  while (!s_isQuitting)
  {
    //TODO: do I need this????

    //ProcessMessages();
    /*Update the stages*/
    M5StageManager::Update();

    /*If the game manager quit, then the application needs to*/
    if (M5StageManager::IsQuitting())
      SendMessage(s_window, WM_CLOSE, 0, 0);
  }
}
/******************************************************************************/
/*!
Shuts down and resources the application has allocated.  This should be called
last.

\attention
You MUST call this last after everything else has been closed!!!
*/
/******************************************************************************/
void M5App::Shutdown(void)
{
  /* Switch Back To The Desktop mode if we are in full screen*/
  if (s_isFullScreen)
    ChangeDisplaySettings(NULL, 0);

  M5ObjectManager::Shutdown();
  /*Shut down StageMgr*/
  M5StageManager::Shutdown();
  /*Clean up windows*/
  UnregisterClass(CLASS_NAME, s_instance);

  //destroy the debug console if it was created.
  M5Debug::DestroyConsole(true);
}
/******************************************************************************/
/*!
Gets the width and height of the client area of the window.

\return
The width and height of the client area of the window.
*/
/******************************************************************************/
M5Vec2 M5App::GetResolution(void)
{
  return M5Vec2((float)s_width, (float)s_height);
}
/******************************************************************************/
/*!
Returns true if the window is fullscreen, false otherwise

\return
Returns true if the window is fullscreen, false otherwise
*/
/******************************************************************************/
bool M5App::GetFullScreen(void)
{
	return s_isFullScreen;
}
/******************************************************************************/
/*!
Allows user to request that the game is visable, or not.

\param [in] showWindow
True if the window should be shown, false otherwise.
*/
/******************************************************************************/
void M5App::ShowWindow(bool showWindow)
{
  //call windows show window function
  ::ShowWindow(s_window, showWindow);
}
/******************************************************************************/
/*!
Allows user to request that the windows mouse cursor is visable, or not.

\param [in] showCursor
True if the window should be show the cursor, false otherwise.
*/
/******************************************************************************/
void M5App::ShowCursor(bool showCursor)
{
  //call windows show cursor function
  ::ShowCursor(showCursor);
}
/******************************************************************************/
/*!
Allows the user to change the resolution of the window.

\param [in] width
The new width of the client area of the window.

\param [in] height
The new height of the client area of the window.
*/
/******************************************************************************/
void M5App::SetResolution(int width, int height)
{
  s_width = width;
  s_height = height;
  M5Gfx::SetResolution(width, height);
  SetFullScreen(s_isFullScreen);
}
/******************************************************************************/
/*!
The function to handle all of the windows messages.

\param [in] win
The window that received the message.

\param [in] msg
The message that was passed.

\param [in] wp
The WPARAM this is filled with different data for each message.

\param [in] lp
The LPARAM This is filled with different data for each message.

\return
The result of the default windows procedure or 0.
*/
/******************************************************************************/
LRESULT CALLBACK M5App::M5WinProc(HWND win, UINT msg, WPARAM wp, LPARAM lp)
{
  switch (msg)
  {
  case WM_CREATE:
  {
    /*Once the window is create M5 can start graphics*/
    M5Gfx::Init(win, s_width, s_height);
    break;
  }
  case WM_DESTROY:
  {
    /*Clean resources here*/
    s_isQuitting = true;
    s_window = 0;
    PostQuitMessage(0);
    break;
  }
  case WM_SIZE:
  {
    /*Update my app data*/
    RECT size;
    GetClientRect(win, &size);
    s_width = size.right - size.left;
    s_height = size.bottom - size.top;
    break;
  }
  case WM_CLOSE:
  {
    if (!M5StageManager::IsQuitting())
    {
      M5StageManager::Quit();
    }
    else
    {
      /*If we want to quit, destroy graphics and the window*/
      M5Gfx::Shutdown();
      DestroyWindow(win);
    }
    break;
  }
  case WM_KEYDOWN:
    M5Input::SetPressed(TranslateKey(wp), true);
    break;
  case WM_KEYUP:
    M5Input::SetPressed(TranslateKey(wp), false);
    break;
  case WM_MOUSEMOVE:
    M5Input::SetMouse(GET_X_LPARAM(lp), s_height - GET_Y_LPARAM(lp));
    break;
  case WM_LBUTTONDOWN:
    M5Input::SetPressed(M5_MOUSE_LEFT, true);
    break;
  case WM_LBUTTONUP:
    M5Input::SetPressed(M5_MOUSE_LEFT, false);
    break;
  case WM_RBUTTONDOWN:
    M5Input::SetPressed(M5_MOUSE_RIGHT, true);
    break;
  case WM_RBUTTONUP:
    M5Input::SetPressed(M5_MOUSE_RIGHT, false);
    break;
  case WM_MBUTTONDOWN:
    M5Input::SetPressed(M5_MOUSE_MIDDLE, true);
    break;
  case WM_MBUTTONUP:
    M5Input::SetPressed(M5_MOUSE_MIDDLE, false);
    break;

  case WM_MOUSEWHEEL:
  {
    short direction = GET_WHEEL_DELTA_WPARAM(wp);

    if (direction > 0)
    {
      M5Input::SetPressed(M5_MOUSE_MIDDLE_UP, true);
      /*Set it to off so it is only active this frame*/
      M5Input::SetPressed(M5_MOUSE_MIDDLE_UP, false);
    }
    else if (direction < 0)
    {
      M5Input::SetPressed(M5_MOUSE_MIDDLE_DOWN, true);
      /*Set it to off so it is only active this frame*/
      M5Input::SetPressed(M5_MOUSE_MIDDLE_DOWN, false);
    }

  }
  break;
  default:
    return DefWindowProc(win, msg, wp, lp);
  }

  return 0;
}



