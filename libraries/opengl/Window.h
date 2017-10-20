#pragma once
#include <glew\glew.h>
#include <glfw\glfw3.h>
#include "Keyboard.h"
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <bitset>

namespace opengl
{
	//class DerivedConcept : public Window<DerivedConcept>
	//{
	//public:
	//	void OnWindowResized ( const int width, const int height )
	//	{

	//	}
	//	void OnFrameBufferResized ( const int width, const int height )
	//	{

	//	}
	//	void OnCharacterEntered ( const unsigned character )
	//	{

	//	}
	//	void OnKeyEntered ( const Key key )
	//	{

	//	}
	//	void OnFileDropped ( const std::string& file_path )
	//	{

	//	}
	//	void OnMouseEnter ( )
	//	{

	//	}
	//	void OnMouseExit ( )
	//	{

	//	}
	//	void OnMouseMove ( const double xpos, const double ypos )
	//	{

	//	}
	//	void OnScroll ( const double xoffset, const double yoffset )
	//	{

	//	}
	//};
	template<class Derived, class Renderer>
	class Window
	{
	public:
		template<class Type>
		struct SizeTemplate
		{
			Type x;
			Type y;
		};

		using Size = SizeTemplate<int>;
		using MousePosition = SizeTemplate<double>;

		explicit Window ( const std::string& name, const unsigned size_x, const unsigned size_y, const bool fullscreen ) : handle_ { CreateHandle ( name, size_x, size_y, fullscreen ) }
		{
			GLFWwindow*const window = handle_.get ( );

			//give glfw the pointer to this
			SetUserPointer ( );

			//Setting up the different callbacks
			glfwSetWindowSizeCallback ( window, [ ] ( GLFWwindow* window, int width, int height )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				derived_window.OnWindowResized ( width, height );
			} );
			glfwSetFramebufferSizeCallback ( window, [ ] ( GLFWwindow* window, int width, int height )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				derived_window.OnFrameBufferResized ( width, height );
			} );
			glfwSetCharCallback ( window, [ ] ( GLFWwindow* window, unsigned character )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				derived_window.OnCharacterEntered ( character );
			} );
			glfwSetKeyCallback ( window, [ ] ( GLFWwindow* window, int key, int scancode, int action, int mods )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				std::bitset<4> modifiers = mods;

				derived_window.OnKeyEntered ( Key ( KEYS ( key ), KEY_STATE ( action ), modifiers, scancode ) );
			} );
			glfwSetDropCallback ( window, [ ] ( GLFWwindow* window, int count, const char** paths )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				for ( std::size_t i = 0; i < static_cast< std::size_t >( count ); ++i )
				{
					derived_window.OnFileDropped ( paths [ i ] );
				}
			} );
			glfwSetMouseButtonCallback ( window, [ ] ( GLFWwindow* window, int button, int action, int mods )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				std::bitset<4> modifiers = mods;

				derived_window.OnKeyEntered ( Key ( KEYS ( button ), KEY_STATE ( action ), modifiers, 0 ) );
			} );
			glfwSetCursorPosCallback ( window, [ ] ( GLFWwindow* window, double xpos, double ypos )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				derived_window.OnMouseMove ( xpos, ypos );
			} );
			glfwSetCursorEnterCallback ( window, [ ] ( GLFWwindow* window, int entered )
			{
				if ( entered == GL_TRUE )
				{
					Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

					derived_window.OnMouseEnter ( );
				}
				else if ( entered == GL_FALSE )
				{
					Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

					derived_window.OnMouseExit ( );
				}
			} );
			glfwSetScrollCallback ( window, [ ] ( GLFWwindow* window, double xoffset, double yoffset )
			{
				Derived& derived_window = static_cast< Derived& >( Window::GetWindow ( window ) );

				derived_window.OnScroll ( xoffset, yoffset );
			} );
		}
		~Window ( )
		{
			MakeContextCurrent ( );
		}

		Window ( const Window& window ) = delete;
		Window& operator=( const Window& window ) = delete;

		Window ( Window&& window ) : handle_ { std::move ( window.handle_ ) }
		{
			SetUserPointer ( );
		}
		Window& operator=( Window&& window )
		{
			this->~Window ( );
			new ( this ) Window { std::move ( window ) };
			return *this;
		}

		bool Initialized ( ) const
		{
			return bool { handle_ };
		}

		bool ShouldClose ( ) const
		{
			return glfwWindowShouldClose ( handle_.get ( ) ) != 0;
		}
		void SetToClose ( )
		{
			glfwSetWindowShouldClose ( handle_.get ( ), GL_TRUE );
		}

		Size GetSize ( ) const
		{
			Size size;
			glfwGetWindowSize ( handle_.get ( ), &size.x, &size.y );
			return size;
		}

		//unsigned char pixels [ 16 * 16 * 4 ];
		//memset ( pixels, 0xff, sizeof ( pixels ) );
		//GLFWimage image;
		//image.width = 16;
		//image.height = 16;
		//image.pixels = pixels;
		//GLFWcursor* cursor = glfwCreateCursor ( &image, 0, 0 );

		// GLFWcursor* cursor = glfwCreateStandardCursor ( GLFW_HRESIZE_CURSOR );
		//GLFW_ARROW_CURSOR
		//GLFW_IBEAM_CURSOR
		//GLFW_CROSSHAIR_CURSOR
		//GLFW_HAND_CURSOR
		//GLFW_HRESIZE_CURSOR
		//GLFW_VRESIZE_CURSOR

		// glfwDestroyCursor(cursor);

		// glfwSetCursor(window, cursor);

		// glfwSetCursor(window, nullptr);
	protected:
		static Window& GetWindow ( GLFWwindow* window )
		{
			return *reinterpret_cast< Window* >( glfwGetWindowUserPointer ( window ) );
		}

		void Fullscreen ( )
		{
			glfwSetWindowMonitor ( handle_.get ( ), glfwGetPrimaryMonitor ( ), 0, 0, 0, 0, GLFW_DONT_CARE );
		}
		void Windowed ( const int top_left_x, const int top_left_y, const int width, const int height )
		{
			glfwSetWindowMonitor ( handle_.get ( ), nullptr, top_left_x, top_left_y, width, height, GLFW_DONT_CARE );
		}

		void MakeContextCurrent ( )
		{
			glfwMakeContextCurrent ( handle_.get ( ) );
		}
		void SwapBuffers ( )
		{
			glfwSwapBuffers ( handle_.get ( ) );
		}

		std::string GetClipboard ( )
		{
			return glfwGetClipboardString ( handle_.get ( ) );
		}
		void SetClipboard ( const std::string& string )
		{
			glfwSetClipboardString ( handle_.get ( ), string.c_str ( ) );
		}

		std::string GetKeyName ( const Key& key ) const
		{
			return glfwGetKeyName ( GLFW_KEY_UNKNOWN, key.GetScanCode ( ) );
		}

		void UseLockedMouse ( )
		{
			const auto window = handle_.get ( );

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		void UseNormalMouse ( )
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		SizeTemplate<double> GetMousePosition ( )
		{
			double x;
			double y;
			glfwGetCursorPos ( handle_.get ( ), &x, &y );
			return { x, y };
		}

	private:
		class Deleter
		{
		public:
			void operator()( GLFWwindow*const window ) const noexcept 
			{
				glfwDestroyWindow ( window );
			}
		};
		using Handle = std::unique_ptr<GLFWwindow, Deleter>;

		static GLFWwindow* CreateHandle ( const std::string& name, const unsigned size_x, const unsigned size_y, const bool fullscreen )
		{
			//Set the GLFW window creation hints - these are optional

			//Request 4x antialiasing
			glfwWindowHint ( GLFW_SAMPLES, 4 );
			//Request a specific OpenGL version
			glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
			//Request a specific OpenGL version
			glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 );
			//To make MacOS happy; should not be needed
			glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
			//We don't want the old OpenGL
			glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

			//Get the address of the monitor if fullscreen is enabled
			GLFWmonitor*const monitor = fullscreen ? glfwGetPrimaryMonitor ( ) : nullptr;

			//Create a window and create its OpenGL context
			GLFWwindow* window = glfwCreateWindow ( size_x, size_y, name.c_str ( ), monitor, nullptr );

			//If the window couldn't be created
			if ( window == nullptr )
			{
				throw std::runtime_error { "Failed to create window!" };
			}
			glfwMakeContextCurrent ( window );
			return window;
		}

		void SetUserPointer ( )
		{
			glfwSetWindowUserPointer ( handle_.get ( ), this );
		}

		Handle handle_;
	protected:
		Renderer renderer_;
	};
}