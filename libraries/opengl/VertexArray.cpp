#include "VertexArray.h"

static GLuint current_id { };

namespace opengl
{
	VertexArray::VertexArray ( ) noexcept : handle_ { CreateHandle ( ) }
	{
	}

	bool VertexArray::Initialized ( ) const noexcept
	{
		return bool { handle_ };
	}

	void VertexArray::Bind ( ) const noexcept
	{
		glBindVertexArray ( handle_.get ( ) );
	}

	GLuint VertexArray::CreateHandle ( ) noexcept
	{
		GLuint id;
		glGenVertexArrays ( 1, &id );
		return id;
	}

	void VertexArray::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		glDeleteVertexArrays ( 1, &pointer );
	}
}