#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <chrono>
#include <random>
#include <winsock\Application.h>
#include <winsock\Server.h>
#include <winsock\Exception.h>
#include "Application.h"

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "winsock.lib")
#pragma comment(lib, "opengl.lib")
#pragma comment(lib, "math.lib")

int main ( )
{
	try
	{
		Application app;
		app.Run ( );
		return 0;
	}
	catch ( const std::exception& exception )
	{
		std::cout << exception.what ( ) << std::endl;
	}

	system ( "pause" );
	return 11;
}