#include "Application.h"
#include <iostream>

#include "Application.h"

#pragma comment(lib, "data_structure.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

static std::string error_;

namespace opengl
{
	Application::Application ( ) : handle_ { CreateHandle ( ) }
	{
	}

	bool Application::Initialized ( ) const
	{
		return bool { handle_ };
	}

	void Application::PollEvents ( )
	{
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents ( );
		gamepad_manager_.UpdateJoysticks ( );
	}

	const Gamepad::Manager::Gamepads& Application::GetGamepads ( ) const noexcept
	{
		return gamepad_manager_.GetGamepads ( );
	}

	bool Application::CreateHandle ( )
	{
		//Set the error callback
		glfwSetErrorCallback ( [ ] ( const int error, const char* description )
		{
			error_ = description;
		}
		);

		if ( glfwInit ( ) == GLFW_FALSE )
		{
			throw std::runtime_error { error_.c_str ( ) };
		}

		return true;
	}

	void Application::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		glfwTerminate ( );
	}
}