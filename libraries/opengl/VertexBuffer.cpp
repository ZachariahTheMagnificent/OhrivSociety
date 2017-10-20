#include "VertexBuffer.h"

namespace opengl
{
	void VertexBuffer::Bind ( ) const noexcept
	{
		Buffer::Bind ( TARGET );
	}

	void VertexBuffer::EnableAttribute ( const GLuint attribute ) noexcept
	{
		glEnableVertexAttribArray ( attribute );
	}

	void VertexBuffer::DisableAttribute ( const GLuint attribute ) noexcept
	{
		glDisableVertexAttribArray ( attribute );
	}

	void VertexBuffer::SetAttribute ( GLbyte, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_BYTE, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLubyte, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_UNSIGNED_BYTE, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLshort, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_SHORT, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLushort, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_UNSIGNED_SHORT, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLint, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_INT, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLuint, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribIPointer ( attribute, num_components, GL_UNSIGNED_INT, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLfloat, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribPointer ( attribute, num_components, GL_FLOAT, GL_FALSE, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( GLdouble, const GLuint attribute, const GLint num_components, const GLsizei stride, const std::size_t offset ) noexcept
	{
		glVertexAttribLPointer ( attribute, num_components, GL_DOUBLE, stride, ( GLvoid* ) offset );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLbyte, 1>& values ) noexcept
	{
		glVertexAttribI1i ( attribute, values [ 0 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLbyte, 2>& values ) noexcept
	{
		glVertexAttribI2i ( attribute, values [ 0 ], values [ 1 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLbyte, 3>& values ) noexcept
	{
		glVertexAttribI3i ( attribute, values [ 0 ], values [ 1 ], values [ 2 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLbyte, 4>& values ) noexcept
	{
		glVertexAttribI4i ( attribute, values [ 0 ], values [ 1 ], values [ 2 ], values [ 3 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLubyte, 1>& values ) noexcept
	{
		glVertexAttribI1ui ( attribute, values [ 0 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLubyte, 2>& values ) noexcept
	{
		glVertexAttribI2ui ( attribute, values [ 0 ], values [ 1 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLubyte, 3>& values ) noexcept
	{
		glVertexAttribI3ui ( attribute, values [ 0 ], values [ 1 ], values [ 2 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLubyte, 4>& values ) noexcept
	{
		glVertexAttribI4ui ( attribute, values [ 0 ], values [ 1 ], values [ 2 ], values [ 3 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLshort, 1>& values ) noexcept
	{
		glVertexAttribI1i ( attribute, values [ 0 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLshort, 2>& values ) noexcept
	{
		glVertexAttribI2i ( attribute, values [ 0 ], values [ 1 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLshort, 3>& values ) noexcept
	{
		glVertexAttribI3i ( attribute, values [ 0 ], values [ 1 ], values [ 2 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLshort, 4>& values ) noexcept
	{
		glVertexAttribI4i ( attribute, values [ 0 ], values [ 1 ], values [ 2 ], values [ 3 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLushort, 1>& values ) noexcept
	{
		glVertexAttribI1ui ( attribute, values [ 0 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLushort, 2>& values ) noexcept
	{
		glVertexAttribI2ui ( attribute, values [ 0 ], values [ 1 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLushort, 3>& values ) noexcept
	{
		glVertexAttribI3ui ( attribute, values [ 0 ], values [ 1 ], values [ 2 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLushort, 4>& values ) noexcept
	{
		glVertexAttribI4ui ( attribute, values [ 0 ], values [ 1 ], values [ 2 ], values [ 3 ] );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLint, 1>& values ) noexcept
	{
		glVertexAttribI1iv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLint, 2>& values ) noexcept
	{
		glVertexAttribI2iv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLint, 3>& values ) noexcept
	{
		glVertexAttribI3iv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLint, 4>& values ) noexcept
	{
		glVertexAttribI4iv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLuint, 1>& values ) noexcept
	{
		glVertexAttribI1uiv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLuint, 2>& values ) noexcept
	{
		glVertexAttribI2uiv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLuint, 3>& values ) noexcept
	{
		glVertexAttribI3uiv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLuint, 4>& values ) noexcept
	{
		glVertexAttribI4uiv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLfloat, 1>& values ) noexcept
	{
		glVertexAttrib1fv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLfloat, 2>& values ) noexcept
	{
		glVertexAttrib2fv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLfloat, 3>& values ) noexcept
	{
		glVertexAttrib3fv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLfloat, 4>& values ) noexcept
	{
		glVertexAttrib4fv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLdouble, 1>& values ) noexcept
	{
		glVertexAttribL1dv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLdouble, 2>& values ) noexcept
	{
		glVertexAttribL2dv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLdouble, 3>& values ) noexcept
	{
		glVertexAttribL3dv ( attribute, values.data ( ) );
	}

	void VertexBuffer::SetAttribute ( const GLuint attribute, const std::array<GLdouble, 4>& values ) noexcept
	{
		glVertexAttribL4dv ( attribute, values.data ( ) );
	}

	void VertexBuffer::Render ( const GLenum mode, const GLint begin, const GLsizei count ) noexcept
	{
		glDrawArrays ( mode, begin, count );
	}
}