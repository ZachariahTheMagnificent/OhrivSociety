#pragma once
#include <glew\glew.h>
#include <glfw\glfw3.h>
#include "Window.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

namespace opengl
{
	// glfwWaitEvents();
	// glfwWaitEventsTimeout ( 0.7 );
	// glfwPostEmptyEvent();
	class Application
	{
	public:
		Application ( );

		Application ( const Application& ) = delete;
		Application& operator=( const Application& ) = delete;

		Application ( Application&& app ) = default;
		Application& operator=( Application&& app ) = default;

		bool Initialized ( ) const;

	protected:
		void PollEvents ( );

		const Gamepad::Manager::Gamepads& GetGamepads ( ) const noexcept;

	private:
		class Deleter
		{
		public:
			using pointer = bool;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<bool, Deleter>;

		static bool CreateHandle ( );

		Handle handle_;
		Gamepad::Manager gamepad_manager_;
	};
}