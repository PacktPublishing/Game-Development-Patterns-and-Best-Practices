/******************************************************************************/
/*!
file    M5Random.c
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    Class:
\par    Assignment:
\date   2012/12/25

This file has functions to get random numbers.
*/
/******************************************************************************/
#include <cstdlib>// for rand and srand

namespace M5Random
{
/******************************************************************************/
/*!
Seeds the random number generator.  This is called once when the engine is
initilizing.  You don't need to call it again, unless you are are trying
to test and want the same seed every time.

\attention This is called once when the engine is initilizing.  You don't
need to call it again, unless you are are trying to test and want the
same seed every time.

\param seed
The value to seed the random number generator.
*/
/******************************************************************************/
void  Seed(unsigned seed)
{
  std::srand(seed);
}
/******************************************************************************/
/*!
Gets a random int between 0 and RAND_MAX defined in cstdlib

\return
A random integer.
*/
/******************************************************************************/
int   GetInt(void)
{
  return std::rand();
}
/******************************************************************************/
/*!
Gets a random integer between the minimum value and max.

\param min
The lowest number in the range.

\param max
The highest number in the range.

\return
A random number between min and max.

*/
/******************************************************************************/
int   GetInt(int min, int max)
{
  int result = std::rand() % (max - min) + 1;
  return result + min;
}
/******************************************************************************/
/*!
Gets a random float between 0 and 1.

\return
A float between 0 and 1.

*/
/******************************************************************************/
float GetFloat(void)
{
  return std::rand() / static_cast<float>(RAND_MAX);
}
/******************************************************************************/
/*!
Gets a random float between the minimum value and the maximum value.

\param min
The lowest number in the range.

\param max
The highest number in the range.

\return
A random number between min and max.

*/
/******************************************************************************/
float GetFloat(float min, float max)
{
  float result = GetFloat() * (max - min);
  return result + min;
}
}//end namespace Random



