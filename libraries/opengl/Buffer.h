#pragma once
#include <memory>
#include <glew\glew.h>

namespace opengl
{
	class Buffer
	{
	public:
		Buffer ( ) noexcept;

		Buffer ( const Buffer& ) = delete;
		Buffer& operator=( const Buffer& ) = delete;

		Buffer ( Buffer&& ) = default;
		Buffer& operator=( Buffer&& ) = default;

		bool Initialized ( ) const noexcept;

	protected:
		void Bind ( const GLenum target ) const noexcept;
		template<class Buffer>
		static void Set ( const GLenum target, const Buffer& buffer ) noexcept
		{
			glBufferData ( target, sizeof ( buffer [ 0 ] ) * ( std::end ( buffer ) - std::begin ( buffer ) ), &buffer [ 0 ], GL_STATIC_DRAW );
		}

	private:
		static GLuint CreateHandle ( ) noexcept;

		class Deleter
		{
		public:
			using pointer = GLuint;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<GLuint, Deleter>;

		Handle handle_ { };
	};
}