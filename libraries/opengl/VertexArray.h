#pragma once
#include <memory>
#include <glew\glew.h>

namespace opengl
{
	class VertexArray
	{
	public:
		VertexArray ( ) noexcept;

		VertexArray ( const VertexArray& vertex_array ) = delete;
		VertexArray& operator=( const VertexArray& vertex_array ) = delete;

		VertexArray ( VertexArray&& vertex_array ) = default;
		VertexArray& operator=( VertexArray&& vertex_array ) = default;

		bool Initialized ( ) const noexcept;

		void Bind ( ) const noexcept;

	private:
		static GLuint CreateHandle ( ) noexcept;

		class Deleter
		{
		public:
			using pointer = GLuint;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<GLuint, Deleter>;

		Handle handle_;
	};
}