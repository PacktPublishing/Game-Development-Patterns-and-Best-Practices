#include <iostream>
#include <cstdlib>
#include <ctime>

//Fills array with random values from 0 to maxVal - 1
void RandomFill(int* array, int size, int maxVal)
{
	for (int i = 0; i < size; ++i)
		array[i] = std::rand() % maxVal;
}
//Fills array with value
void ValueFill(int* array, int size, int value)
{
	for (int i = 0; i < size; ++i)
		array[i] = value;
}
//Fills array with ordered values from 0 - maxVal - 1 repeatedly
void ModFill(int* array, int size, int maxVal)
{
	for (int i = 0; i < size; ++i)
		array[i] = i % maxVal;
}
//Helper to print array
void PrintArray(const int* array, int size)
{
	for (int i = 0; i < size; ++i)
		std::cout << array[i] << " ";
	std::cout << std::endl;
}

//Without typedef 
//void FillAndPrint(void (*fillFunc)(int*, int, int),int* array, int size int param)

typedef void(*FillFunc)(int*, int, int);

void FillAndPrint(FillFunc pFunc, int* array, int size, int param)
{

	pFunc(array, size, param);
	PrintArray(array, size);
}
FillFunc FillFactoryMethod(int index)
{
	switch (index)
	{
	case 0:
		return RandomFill;
	case 1:
		return ValueFill;
	default:
		//We could report an error if the value is outside of the 
		//range, but instead we just use a default
		return ModFill;
	}
}
/* Our First main example
int main(void)
{
	const int SIZE = 20;
	int array[SIZE];
	//See the Random number generator
	std::srand(static_cast<unsigned>(time(0)));
	FillAndPrint(ValueFill, array, 20, 3);
	FillAndPrint(RandomFill, array, 10, 5);

	return 0;
}*/
/* Our Second main example */
int main(void)
{
const int SIZE = 20;
int array[SIZE];
int fillChoice;
int param;

//This doesn't properly explain to the user, but it is just an example
std::cout << "Enter a Fill Mode and parameter to use" << std::endl;
std::cin >> fillChoice;
std::cin >> param;
//See the Random number generator
std::srand(static_cast<unsigned>(time(0)));
FillAndPrint(FillFactoryMethod(fillChoice), array, 20, param);

return 0;
}