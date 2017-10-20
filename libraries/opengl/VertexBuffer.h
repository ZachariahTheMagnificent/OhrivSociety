#pragma once
#include <array>
#include "Buffer.h"

namespace opengl
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer ( ) = default;

		VertexBuffer ( const VertexBuffer& ) = delete;
		VertexBuffer& operator=( const VertexBuffer& ) = delete;

		VertexBuffer ( VertexBuffer&& ) = default;
		VertexBuffer& operator=( VertexBuffer&& ) = default;

		void Bind ( ) const noexcept;

		template<class Container>
		static void Set ( const Container& buffer ) noexcept
		{
			Buffer::Set ( TARGET, buffer );
		}

		static void EnableAttribute ( const GLuint attribute ) noexcept;
		static void DisableAttribute ( const GLuint attribute ) noexcept;

		static void SetAttribute ( GLbyte, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLubyte, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLshort, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLushort, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLint, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLuint, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLfloat, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;
		static void SetAttribute ( GLdouble, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLbyte, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLbyte, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLbyte, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLbyte, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLubyte, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLubyte, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLubyte, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLubyte, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLshort, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLshort, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLshort, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLshort, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLushort, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLushort, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLushort, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLushort, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLint, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLint, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLint, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLint, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLuint, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLuint, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLuint, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLuint, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLfloat, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLfloat, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLfloat, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLfloat, 4>& values ) noexcept;

		static void SetAttribute ( const GLuint attribute, const std::array<GLdouble, 1>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLdouble, 2>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLdouble, 3>& values ) noexcept;
		static void SetAttribute ( const GLuint attribute, const std::array<GLdouble, 4>& values ) noexcept;

		static void Render ( const GLenum mode, const GLint begin, const GLsizei count ) noexcept;

	private:
		static constexpr GLenum TARGET = GL_ARRAY_BUFFER;
	};
}