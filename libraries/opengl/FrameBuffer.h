#pragma once
#include "Texture.h"

namespace opengl
{
	enum class FRAME_BUFFER_MODE
	{
		DEPTH_STENCIL,
		DEPTH,
		PURE_COLOUR
	};

	template<FRAME_BUFFER_MODE mode, class Derived>
	class DepthStencilFrameBuffer
	{
	public:
		void BindDepthStencilTexture ( ) noexcept
		{
			Derived& derived = static_cast< Derived& >( *this );
			derived.textures_.front ( ).Bind ( );
		}

	protected:
		DepthStencilFrameBuffer ( ) = default;

		template<class Setter>
		void SetDepthStencil ( Texture& texture, Setter&& setter )
		{
			setter.SetDepthStencil ( texture );
		}
		template<class Setter>
		void SetDepth ( Texture& texture, Setter&& setter )
		{
		}
	};

	template<class Derived>
	class DepthStencilFrameBuffer<FRAME_BUFFER_MODE::DEPTH, Derived>
	{
	public:
		void BindDepthTexture ( ) noexcept
		{
			Derived& derived = static_cast< Derived& >( *this );
			derived.textures_.front ( ).Bind ( );
		}

	protected:
		DepthStencilFrameBuffer ( ) = default;

		template<class Setter>
		void SetDepthStencil ( Texture& texture, Setter&& setter )
		{
		}
		template<class Setter>
		void SetDepth ( Texture& texture, Setter&& setter )
		{
			setter.SetDepth ( texture );
		}
	};

	template<class Derived>
	class DepthStencilFrameBuffer<FRAME_BUFFER_MODE::PURE_COLOUR, Derived>
	{
	protected:
		DepthStencilFrameBuffer ( ) = default;

		template<class Setter>
		void SetDepthStencil ( Texture& texture, Setter&& setter )
		{
		}
		template<class Setter>
		void SetDepth ( Texture& texture, Setter&& setter )
		{
		}
	};

	template<std::size_t num_colours, class Derived>
	class ColourFrameBuffer
	{
	public:
		void BindColourTexture ( const std::size_t colour_index ) noexcept
		{
			Derived& derived = static_cast< Derived& >( *this );
			derived.textures_ [ derived.colour_texture_start_index + colour_index ].Bind ( );
		}

	protected:
		ColourFrameBuffer ( ) = default;

		template<class Setter>
		void SetColour ( const GLuint index, Texture& texture, Setter&& setter )
		{
			setter.SetColour ( index, texture );
		}
	};

	template<class Derived>
	class ColourFrameBuffer<1, Derived>
	{
	public:
		void BindColourTexture ( ) noexcept
		{
			Derived& derived = static_cast< Derived& >( *this );
			derived.textures_ [ derived.colour_texture_start_index ].Bind ( );
		}

	protected:
		ColourFrameBuffer ( ) = default;

		template<class Setter>
		void SetColour ( const GLuint index, Texture& texture, Setter&& setter )
		{
			setter.SetColour ( index, texture );
		}
	};

	template<class Derived>
	class ColourFrameBuffer<0, Derived>
	{
	protected:
		ColourFrameBuffer ( ) = default;

		template<class Setter>
		void SetColour ( const GLuint index, Texture& texture, Setter&& setter )
		{
		}
	};

	template<FRAME_BUFFER_MODE mode, std::size_t num_colours>
	class FrameBuffer : private Texture::FrameBuffer, public DepthStencilFrameBuffer<mode, FrameBuffer<mode, num_colours>>, public ColourFrameBuffer<num_colours, FrameBuffer<mode, num_colours>>
	{
	public:
		friend DepthStencilFrameBuffer;
		friend ColourFrameBuffer;

		FrameBuffer ( )
		{

		}
		template<class Setter>
		FrameBuffer ( Setter&& setter )
		{
			Bind ( );
			SetTextures ( std::forward<Setter> ( setter ) );
		}

		void Bind ( ) noexcept
		{
			glBindFramebuffer ( GL_FRAMEBUFFER, handle_.get ( ) );
		}
		void UnBind ( ) noexcept
		{
			glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
		}

		template<class Setter>
		void SetTextures ( Setter&& setter )
		{
			// Set our depth stencil texture if included
			if ( mode == FRAME_BUFFER_MODE::DEPTH_STENCIL )
			{
				auto& texture = textures_.front ( );

				SetDepthStencil ( texture, std::forward<Setter> ( setter ) );

				AddFrameBufferTexture ( texture, GL_DEPTH_STENCIL_ATTACHMENT, 0 );
			}
			// Set our depth texture if included
			else if ( mode == FRAME_BUFFER_MODE::DEPTH )
			{
				auto& texture = textures_.front ( );

				SetDepth ( texture, std::forward<Setter> ( setter ) );

				AddFrameBufferTexture ( texture, GL_DEPTH_ATTACHMENT, 0 );
			}


			// Set the list of draw buffers.
			std::vector<GLenum> draw_buffers ( num_colours );

			// Set our textures as the attachment
			for ( GLuint i = 0; i < num_colours; ++i )
			{
				const GLenum attachment = GL_COLOR_ATTACHMENT0 + i;

				auto& texture = textures_ [ colour_texture_start_index + i ];

				SetColour ( i, texture, std::forward<Setter> ( setter ) );

				AddFrameBufferTexture ( texture, attachment, 0 );
				draw_buffers [ i ] = attachment;
			}

			glDrawBuffers ( draw_buffers.size ( ), &draw_buffers.front ( ) );

			if ( glCheckFramebufferStatus ( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			{
				throw std::runtime_error { "Unsupported Framebuffer!" };
			}
		}

	private:
		class Deleter
		{
		public:
			using pointer = GLuint;

			void operator()( const pointer& pointer ) const noexcept
			{
				glDeleteFramebuffers ( 1, &pointer );
			}
		};
		using Handle = std::unique_ptr<GLuint, Deleter>;

		static GLuint CreateHandle ( ) noexcept
		{
			// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
			GLuint handle { };
			glGenFramebuffers ( 1, &handle );
			return handle;
		}

		static constexpr std::size_t colour_texture_start_index = mode != FRAME_BUFFER_MODE::PURE_COLOUR ? 1 : 0;
		static constexpr std::size_t num_textures = colour_texture_start_index + num_colours;

		Handle handle_ { CreateHandle ( ) };
		std::vector<Texture> textures_ { num_textures };
	};
}