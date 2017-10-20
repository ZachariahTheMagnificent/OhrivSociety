#include "Basic.h"
#include <cmath>

#pragma comment(lib, "data_structure.lib")

namespace math
{
	const char* DivideByZero::what ( ) const noexcept
	{
		return "Divide by zero. http://i.imgur.com/90rYhuB.jpg";
	}

	const char* MustBeUnit::what ( ) const noexcept
	{
		return "Must be of unit length to run this operation!";
	}
}