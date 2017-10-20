#include "Buffer.h"

namespace opengl
{
	static thread_local GLuint current_bind;

	opengl::Buffer::Buffer ( ) noexcept : handle_ { CreateHandle ( ) }
	{
	}

	bool Buffer::Initialized ( ) const noexcept
	{
		return bool { handle_ };
	}

	void Buffer::Bind ( const GLenum target ) const noexcept
	{
		glBindBuffer ( target, handle_.get ( ) );
	}

	GLuint Buffer::CreateHandle ( ) noexcept
	{
		GLuint id { };
		glGenBuffers ( 1, &id );
		return id;
	}

	void Buffer::Deleter::operator()( const pointer& pointer ) const noexcept
	{
		glDeleteBuffers ( 1, &pointer );
	}
}