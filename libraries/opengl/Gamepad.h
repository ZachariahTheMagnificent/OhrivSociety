#pragma once
#include <vector>
#include <glfw\glfw3.h>

namespace opengl
{
	class Gamepad
	{
	public:
		class Manager
		{
		public:
			using Gamepads = std::vector<Gamepad>;

			static constexpr std::size_t TOTAL_JOYSTICKS = GLFW_JOYSTICK_LAST + 1;

			Manager ( );

			void UpdateJoysticks ( );

			const Gamepads& GetGamepads ( ) const noexcept;

		private:
			static void PlugInGamepad ( const std::size_t index );
			static void PlugOutGamepad ( const std::size_t index );

			static Gamepads gamepads_;
		};

		Gamepad ( ) = default;

	private:
		std::size_t index { };
		std::string name;
		std::vector<float> axes;
		std::vector<unsigned char> buttons;
	};
}