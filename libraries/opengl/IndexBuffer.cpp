#include "IndexBuffer.h"

namespace opengl
{
	static thread_local GLuint current_bind;

	void IndexBuffer::Bind ( ) const noexcept
	{
		Buffer::Bind ( TARGET );
	}

	void IndexBuffer::Set ( const std::vector<GLuint>& buffer ) noexcept
	{
		Buffer::Set ( TARGET, buffer );
	}

	void IndexBuffer::Render ( const GLenum mode, const GLsizei count, const GLuint begin ) noexcept
	{
		glDrawElements ( mode, count, GL_UNSIGNED_INT, reinterpret_cast< void* >( begin * sizeof ( GLuint ) ) );
	}
}