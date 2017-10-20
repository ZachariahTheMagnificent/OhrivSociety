#pragma once
#include <vector>
#include "Buffer.h"

namespace opengl
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer ( ) = default;

		IndexBuffer ( const IndexBuffer& ) = delete;
		IndexBuffer& operator=( const IndexBuffer& ) = delete;

		IndexBuffer ( IndexBuffer&& ) = default;
		IndexBuffer& operator=( IndexBuffer&& ) = default;

		void Bind ( ) const noexcept;

		static void Set ( const std::vector<GLuint>& buffer ) noexcept;
		static void Render ( const GLenum mode, const GLsizei count, const GLuint begin ) noexcept;

	private:
		static constexpr GLenum TARGET = GL_ELEMENT_ARRAY_BUFFER;
	};
}