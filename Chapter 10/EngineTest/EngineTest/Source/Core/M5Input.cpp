/******************************************************************************/
/*!
file    M5Input.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7


Singleton class to control get and set input.

*/
/******************************************************************************/
#include "M5Input.h"
#include "M5Vec2.h"
#include "M5Debug.h"

#include <cmath>    /*sqrt*/
#include <climits>  /*max short*/
#include <bitset>
#include <stack>

#include <Xinput.h>



namespace
{
const int CONTROLLER_NUM = 0;

std::bitset<M5_LAST>  s_pressed;            /*!< Array of keys pressed this frame*/
std::bitset<M5_LAST>  s_triggered;          /*!< Array of keys triggered this frame*/
std::bitset<M5_LAST>  s_repeating;          /*!< Array of keys repeating this frame*/
std::stack<M5KeyCode> s_unpress;            /*!< The array of keys to unpress*/
XINPUT_STATE          s_gamePadState;       /*!< The stage of the gamePad*/
M5Vec2                s_mouse;              /*!< The Coordinates of the mouse*/
M5Vec2                s_leftThumb;          /*!< The x/y postion of the left thumbstick*/
M5Vec2                s_rightThumb;         /*!< The x/y postion of the right thumbstick*/
float                 s_leftTrigger;        /*!< Array of keys pressed this frame*/
float                 s_rightTrigger;       /*!< Array of keys pressed this frame*/
float                 s_gamePadTimer;       /*!< If we aren't connected, only check every 1 second*/
bool                  s_isGamePadConnected; /*!< Bool to tell if gamePad is connected*/
}//end unnamed namespace


/******************************************************************************/
/*!
Sets the pressed, triggered, repeating, or unpressed stage of a key.

\param [in] key
The key to set

\param [in] status
If the key is being pressed or not.
*/
/******************************************************************************/
void M5Input::SetPressed(M5KeyCode key, int status)
{
  if (key < M5_INVALID || key >= M5_LAST)
    return;

  if (status)/*If the key is pressed*/
  {
    if (s_pressed[key])/*if the key was already pressed*/
    {
      /*Set it as repeating*/
      s_repeating[key] = true;
    }
    else/*The key was not already pressed*/
    {
      /*Set it as triggered and pressed*/
      s_pressed[key] = true;
      s_triggered[key] = true;
    }
  }
  else /*If it is not pressed*/
  {
    /*Put the key on the unpressed stack*/
    s_unpress.push(key);
  }
}
/******************************************************************************/
/*!
Function to allocate and set my initial data for input. THIS IS CALLED
AUTOMATICALLY BY THE SYSTEM.
*/
/******************************************************************************/
void M5Input::Init(void)
{
  M5DEBUG_CALL_CHECK(1);

  s_isGamePadConnected = false;

  /*Clear my arrays*/
  for (int i = 0; i < M5_LAST; ++i)
  {
    s_pressed[i] = false;
    s_triggered[i] = false;
    s_repeating[i] = false;
  }
  //Set my timer to 0
  s_gamePadTimer = 0;
}
/******************************************************************************/
/*!
This function resets my triggered, and repeating data and mouse. This is called
once per frame before getting windows input.

\param dt
The time since the last frame.  This is used to check if the controller is 
plugged in every 1 second (If it is unplugged.)
*/
/******************************************************************************/
void M5Input::Reset(float dt)
{
  /*Only reset the pressed values that are not being pressed*/
  for (size_t i = 0; i < s_unpress.size(); ++i)
  {
    s_pressed[s_unpress.top()] = false;/*Reset the pressed value*/
    s_unpress.pop();
  }

  /*reset my triggered and repeating*/
  for (size_t i = 0; i < M5_LAST; ++i)
  {
    s_triggered[i] = false;
    s_repeating[i] = false;
  }

  if (s_isGamePadConnected)
  {
    /*Do my Gamepad input*/
    GetGamePadButtons();
    s_gamePadTimer = 0;
  }
  else
  {
    s_gamePadTimer += dt;
    if (s_gamePadTimer > 1.f)
    {
      s_gamePadTimer = 0;
      GetGamePadButtons();
    }
  }
}
/******************************************************************************/
/*!
Use this function to check if a specific key is pressed this frame.

\param [in] key
The key to check.

\return
TRUE if the key is pressed, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsPressed(M5KeyCode key)
{
  M5DEBUG_ASSERT((key > M5_INVALID) && (key < M5_LAST), "Key is out of range");
  return s_pressed[key];
}
/******************************************************************************/
/*!
Use this function to check if a specific key is triggered this frame.

\param [in] key
The key to check.

\return
TRUE if the key is triggered, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsTriggered(M5KeyCode key)
{
  M5DEBUG_ASSERT((key > M5_INVALID) && (key < M5_LAST), "Key is out of range");
  return s_triggered[key];
}
/******************************************************************************/
/*!
Use this function to check if a specific key is repeating this frame.

\param [in] key
The key to check.

\return
TRUE if the key is repeating, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsRepeating(M5KeyCode key)
{
  M5DEBUG_ASSERT((key > M5_INVALID) && (key < M5_LAST),"Key is out of range");
  return s_repeating[key];
}
/******************************************************************************/
/*!
Use this function to check if any key is pressed this frame.

\return
TRUE if the any key is pressed, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsAnyPressed(void)
{
  return s_pressed.any();
}
/******************************************************************************/
/*!
Use this function to check if any key is triggered this frame.

\return
TRUE if the any key is triggered, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsAnyTriggered(void)
{
  return s_triggered.any();
}
/******************************************************************************/
/*!
Use this function to check if any key is repeating this frame.

\return
true if the any key is repeating, false otherwise.
*/
/******************************************************************************/
bool M5Input::IsAnyRepeating(void)
{
  return s_repeating.any();
}
/******************************************************************************/
/*!
Use this function to get the x and y coordinates of the mouse.  This function
returns the x and y as floats in a M5Vec2 struct.

\param [out] mouse
A mouse struct to be filled in.

\return
none
*/
/******************************************************************************/
void M5Input::GetMouse(M5Vec2& mouse)
{
  mouse = s_mouse;
}
/******************************************************************************/
/*!
Use this to set x and y coordinates of the mouse. 

\param [in] x The x coordinate of the mouse in screen space

\param [in] y The y coordinate of the mouse in screen space 
*/
/******************************************************************************/
void M5Input::SetMouse(int x, int y)
{
  s_mouse.Set(static_cast<float>(x), static_cast<float>(y));
}
/******************************************************************************/
/*!
Returns true if the Gamepad is connected, false otherwise.

\return
Returns true if the Gamepad is connected, false otherwise.
*/
/******************************************************************************/
bool M5Input::GamePadIsConnected(void)
{
  return s_isGamePadConnected;
}
/******************************************************************************/
/*!
Gets the X and Y values of the left thumb stick.

\param [out] vec
The vec where the values will be stored.

*/
/******************************************************************************/
void M5Input::GetLeftThumb(M5Vec2& vec)
{
  vec = s_leftThumb;
}
/******************************************************************************/
/*!
Gets the X and Y values of the left right stick.

\param [out] vec
The vec where the values will be stored.

*/
/******************************************************************************/
void M5Input::GetRightThumb(M5Vec2& vec)
{
  vec = s_rightThumb;
}
/******************************************************************************/
/*!
Gets the value left trigger.

\return
this value is between 0 to 1
*/
/******************************************************************************/
float M5Input::GetLeftTrigger(void)
{
  return s_leftTrigger;
}
/******************************************************************************/
/*!
Gets the value right trigger.

\return
this value is between 0 and 1
*/
/******************************************************************************/
float M5Input::GetRightTrigger(void)
{
  return s_rightTrigger;
}
/******************************************************************************/
/*!
Helper function to get the state of the game pad and check if it connected.
*/
/******************************************************************************/
void M5Input::GetGamePadState(void)
{
  DWORD result; /*For testing game pad*/
  ZeroMemory(&s_gamePadState, sizeof(XINPUT_STATE));
  result = XInputGetState(CONTROLLER_NUM, &s_gamePadState);
  
  s_isGamePadConnected = (result == ERROR_SUCCESS);
  
}
/******************************************************************************/
/*!
Helper function to Set the pressed state of all GamePad Buttons.
*/
/******************************************************************************/
void M5Input::SetGamePadButtons(void)
{
  SetPressed(M5_GAMEPAD_START,          s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
  SetPressed(M5_GAMEPAD_BACK,           s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
  SetPressed(M5_GAMEPAD_A,              s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
  SetPressed(M5_GAMEPAD_B,              s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_B);
  SetPressed(M5_GAMEPAD_X,              s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_X);
  SetPressed(M5_GAMEPAD_Y,              s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
  SetPressed(M5_GAMEPAD_DPAD_UP,        s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
  SetPressed(M5_GAMEPAD_DPAD_DOWN,      s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
  SetPressed(M5_GAMEPAD_DPAD_LEFT,      s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
  SetPressed(M5_GAMEPAD_DPAD_RIGHT,     s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
  SetPressed(M5_GAMEPAD_LEFT_THUMB,     s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
  SetPressed(M5_GAMEPAD_RIGHT_THUMB,    s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
  SetPressed(M5_GAMEPAD_LEFT_SHOULDER,  s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
  SetPressed(M5_GAMEPAD_RIGHT_SHOULDER, s_gamePadState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
}
/******************************************************************************/
/*!
This function gets the game pad button input from the controller.
*/
/******************************************************************************/
void M5Input::GetGamePadButtons(void)
{
  /*For doing the thumb sticks*/
  float x, y;
  float magnitude;
  float normX, normY;
  float normMagnitude;

  GetGamePadState();
  SetGamePadButtons();//Even if game pad isn't connected, it will zero out the buttons

  if (!s_isGamePadConnected)
    return;

  /*Do the left thumb stick********************************************/
  x = s_gamePadState.Gamepad.sThumbLX;
  y = s_gamePadState.Gamepad.sThumbLY;
  magnitude = std::sqrt(x*x + y*y);
  normX = x / magnitude;
  normY = y / magnitude;

  if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
  {
    if (magnitude > SHRT_MAX)
      magnitude = SHRT_MAX;

    magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
    normMagnitude = magnitude / (SHRT_MAX - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
    s_leftThumb.Set(normX * normMagnitude, normY * normMagnitude);
  }
  else
  {
    s_leftThumb.Set(0, 0);
  }

  /*Do the right thumb stick*/
  x = s_gamePadState.Gamepad.sThumbRX;
  y = s_gamePadState.Gamepad.sThumbRY;
  magnitude = std::sqrt(x*x + y*y);

  normX = x / magnitude;
  normY = y / magnitude;

  if (magnitude > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
  {
    if (magnitude > SHRT_MAX)
      magnitude = SHRT_MAX;

    magnitude -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
    normMagnitude = magnitude / (SHRT_MAX - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
    s_rightThumb.Set(normX * normMagnitude, normY * normMagnitude);
  }
  else
  {
    s_rightThumb.Set(0, 0);
  }




  /*Do left trigger****************************************************/
  magnitude = s_gamePadState.Gamepad.bLeftTrigger;
  if (magnitude > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
  {
    magnitude -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
    magnitude = magnitude / (UCHAR_MAX - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
    s_leftTrigger = magnitude;
  }
  else
    s_leftTrigger = 0;

  /*Do the right trigger*/
  magnitude = s_gamePadState.Gamepad.bRightTrigger;
  if (magnitude > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
  {
    magnitude -= XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
    magnitude = magnitude / (UCHAR_MAX - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
    s_rightTrigger = magnitude;
  }
  else
  {
    s_rightTrigger = 0;
  }

}

