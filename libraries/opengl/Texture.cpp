#include "Texture.h"
#include <limits>

namespace opengl
{
	Texture::Texture ( ) noexcept : handle_ { CreateHandle ( ) }
	{
	}

	Texture::Texture ( const GLsizei width, const GLsizei height, const std::vector<Pixel>& pixels ) noexcept : handle_ { CreateHandle ( ) }
	{
		Fill ( width, height, pixels );
	}

	bool Texture::Initialised ( ) const noexcept
	{
		return bool { handle_ };
	}

	void Texture::Bind ( ) const noexcept
	{
		glBindTexture ( GL_TEXTURE_2D, handle_.get ( ) );
	}

	void Texture::SetActiveSlot ( const std::size_t slot ) noexcept
	{
		glActiveTexture ( GL_TEXTURE0 + slot );
	}

	void Texture::Fill ( const GLsizei width, const GLsizei height, const std::vector<Pixel>& pixels ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels.front ( ) );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetRGBAByte ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetRFloat ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetRGBFloat ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetRGBAFloat ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetDepthStencil ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	void Texture::SetDepth ( const GLsizei width, const GLsizei height ) noexcept
	{
		glTexImage2D ( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );

		// Set anisotropy settings
		GLfloat max_anisotropy = 1.f;
		glGetFloatv ( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ( GLint ) max_anisotropy );
		glGenerateMipmap ( GL_TEXTURE_2D );

		// Set anti-aliasing settings
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		// Set behaviour for uv coords outside of [x = 0.0-1.0][y = 0.0-1.0]
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	}

	GLuint Texture::CreateHandle ( ) noexcept
	{
		GLuint id { };
		glGenTextures ( 1, &id );
		return id;
	}

	void Texture::FrameBuffer::AddFrameBufferTexture ( Texture & texture, const GLenum attachment, const GLint mipmap_levels )
	{
		glFramebufferTexture ( GL_FRAMEBUFFER, attachment, texture.handle_.get ( ), mipmap_levels );
	}

	void Texture::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		glDeleteTextures ( 1, &pointer );
	}
}