#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <chrono>
#include <random>
#include <winsock\Application.h>
#include <winsock\Server.h>
#include <winsock\Exception.h>
#include <math\Vector3.h>
#include <math\Rotation.h>
#include <math\Matrix4x4.h>

#pragma comment(lib, "winsock.lib")
#pragma comment(lib, "math.lib")

using Vector3 = math::Vector3<float>;
using Rotation = math::Rotation<float>;
using Matrix = math::Matrix<float>;

int main ( )
{
	system ( "pause" );
	return 0;
}