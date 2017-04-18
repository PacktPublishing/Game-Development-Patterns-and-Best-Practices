/******************************************************************************/
/*!
\file   M5Input.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7


Singleton class to control get and set input.

*/
/******************************************************************************/
#ifndef M5_INPUT_H
#define M5_INPUT_H

//Forward Declarations
struct M5Vec2;

//! The Mach5 Engine interal set of keys/buttons that can be pressed.
enum M5KeyCode
{
  M5_INVALID,
  M5_BACKSPACE,
  M5_TAB,
  M5_RETURN,
  M5_SHIFT,
  M5_CONTROL,
  M5_CAPS_LOCK,
  M5_ESCAPE,
  M5_SPACE,
  M5_ARROW_UP,
  M5_ARROW_DOWN,
  M5_ARROW_LEFT,
  M5_ARROW_RIGHT,
  M5_0,
  M5_1,
  M5_2,
  M5_3,
  M5_4,
  M5_5,
  M5_6,
  M5_7,
  M5_8,
  M5_9,
  M5_A,
  M5_B,
  M5_C,
  M5_D,
  M5_E,
  M5_F,
  M5_G,
  M5_H,
  M5_I,
  M5_J,
  M5_K,
  M5_L,
  M5_M,
  M5_N,
  M5_O,
  M5_P,
  M5_Q,
  M5_R,
  M5_S,
  M5_T,
  M5_U,
  M5_V,
  M5_W,
  M5_X,
  M5_Y,
  M5_Z,
  M5_F1,
  M5_F2,
  M5_F3,
  M5_F4,
  M5_F5,
  M5_F6,
  M5_F7,
  M5_F8,
  M5_F9,
  M5_F10,
  M5_F11,
  M5_F12,
  M5_SHIFT_LEFT,
  M5_SHIFT_RIGHT,
  M5_CONTROL_LEFT,
  M5_CONTROL_RIGHT,
  M5_MOUSE_LEFT,
  M5_MOUSE_RIGHT,
  M5_MOUSE_MIDDLE,
  M5_MOUSE_MIDDLE_UP,
  M5_MOUSE_MIDDLE_DOWN,
  M5_GAMEPAD_DPAD_UP,
  M5_GAMEPAD_DPAD_DOWN,
  M5_GAMEPAD_DPAD_LEFT,
  M5_GAMEPAD_DPAD_RIGHT,
  M5_GAMEPAD_START,
  M5_GAMEPAD_BACK,
  M5_GAMEPAD_LEFT_THUMB,
  M5_GAMEPAD_RIGHT_THUMB,
  M5_GAMEPAD_LEFT_SHOULDER,
  M5_GAMEPAD_RIGHT_SHOULDER,
  M5_GAMEPAD_A,
  M5_GAMEPAD_B,
  M5_GAMEPAD_X,
  M5_GAMEPAD_Y,
  M5_LAST
};


//! Singleton class to control get and set input.
class M5Input
{
public:
  friend class M5App;
  friend class M5StageManager;

  /*Check if a specific key is being held down*/
  static bool  IsPressed(M5KeyCode key);
  /*Check if a specific key was first touched this frame*/
  static bool  IsTriggered(M5KeyCode key);
  /*Check if key is touched this frame and last frame*/
  static bool  IsRepeating(M5KeyCode key);
  /*Check if any key is being held down*/
  static bool  IsAnyPressed(void);
  /*Check if any key was first touched this frame*/
  static bool  IsAnyTriggered(void);
  /*Check if any key is touched this frame and last*/
  static bool  IsAnyRepeating(void);
  /*Gets the mouse click point in screen space*/
  static void  GetMouse(M5Vec2& pMouse);
  /*Gets the direction of the left thumbstick*/
  static void  GetLeftThumb(M5Vec2& vec);
  /*Gets the direction of the right thumbstick*/
  static void  GetRightThumb(M5Vec2& vec);
  /*Gets the value of the left trigger*/
  static float GetLeftTrigger(void);
  /*Gets the value of the right trigger*/
  static float GetRightTrigger(void);
  /*Lets user know if game pad is connected*/
  static bool  GamePadIsConnected(void);
private:
  static void Init(void);
  static void Reset(float dt);
  static void SetPressed(M5KeyCode key, int status);
  static void SetMouse(int x, int y);
  static void GetGamePadState(void);
  static void GetGamePadButtons(void);
  static void SetGamePadButtons(void);
};//end M5Input




#endif