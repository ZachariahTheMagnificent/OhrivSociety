#include "Gamepad.h"
#include <algorithm>

namespace opengl
{
	Gamepad::Manager::Gamepads Gamepad::Manager::gamepads_;

	Gamepad::Manager::Manager ( )
	{
		glfwSetJoystickCallback ( [ ] ( int joy, int event )
		{
			if ( event == GLFW_CONNECTED )
			{
				PlugInGamepad ( joy );
			}
			else if ( event == GLFW_DISCONNECTED )
			{
				PlugOutGamepad ( joy );
			}
		} );
	}

	void Gamepad::Manager::UpdateJoysticks ( )
	{
		for ( auto& gamepad : gamepads_ )
		{
			// Get the name
			gamepad.name = glfwGetJoystickName ( gamepad.index );

			// Get the axes
			const float* axes;
			int axes_count;

			axes = glfwGetJoystickAxes ( gamepad.index, &axes_count );
			gamepad.axes.resize ( axes_count );
			memcpy ( &gamepad.axes.front ( ), axes, sizeof ( gamepad.axes.front ( ) ) * gamepad.axes.size ( ) );

			// Get the buttons
			const unsigned char* buttons;
			int button_count;

			buttons = glfwGetJoystickButtons ( gamepad.index, &button_count );
			gamepad.buttons.resize ( button_count );
			memcpy ( &gamepad.buttons.front ( ), buttons, sizeof ( gamepad.buttons.front ( ) ) * gamepad.buttons.size ( ) );
		}
	}

	const Gamepad::Manager::Gamepads& Gamepad::Manager::GetGamepads ( ) const noexcept
	{
		return gamepads_;
	}

	void Gamepad::Manager::PlugInGamepad ( const std::size_t index )
	{
		Gamepad gamepad;
		gamepad.index = index;
		gamepads_.push_back ( gamepad );
	}

	void Gamepad::Manager::PlugOutGamepad ( const std::size_t index )
	{
		auto it = std::find_if ( gamepads_.begin ( ), gamepads_.end ( ), [ index ] ( const Gamepad& a )
		{
			return a.index == index;
		} );
		*it = std::move ( gamepads_.back ( ) );
		gamepads_.pop_back ( );
	}
}