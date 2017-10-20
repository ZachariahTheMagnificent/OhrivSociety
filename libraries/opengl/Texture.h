#pragma once
#include <glew\glew.h>
#include <memory>
#include <vector>

namespace opengl
{
	/******************************************************************************/
	/*!
	\brief
	Defines the pixel format used by OpenGL.

	This class is built with the sole purpose of defining the pixel format in
	OpenGL. It is set in an RGBA format arranged in that order using a 1 byte
	integer to represent each value. It is recommended that you use this format for
	all textures even ones that are grayscale or only have alpha values. The
	class's respective constructors would easily allow you to convert pixels of
	other formats to RGBA. Use it with Texture::Fill() to send textures to OpenGL
	by passing it an array of Pixel(s).
	*/
	/******************************************************************************/
	struct Pixel
	{
		/******************************************************************************/
		/*!
		\brief
		Default constructor

		All values would be zero initialized.
		*/
		/******************************************************************************/
		constexpr Pixel ( ) = default;
		/******************************************************************************/
		/*!
		\brief
		Constructor used to set all four values of the pixel

		This constructor is used by the other constructors to construct the pixel.
		If you do not want to set all 4 values of the pixel, the other constructors may
		prove more convenient.

		\param red - the r value of the pixel
		\param green - the g value of the pixel
		\param blue - the b value of the pixel
		\param alpha - the a value of the pixel
		*/
		/******************************************************************************/
		explicit constexpr Pixel ( const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha ) noexcept : red { red }, green { green }, blue { blue }, alpha { alpha }
		{
		}
		/******************************************************************************/
		/*!
		\brief
		Constructor used to set only the rgb values of the pixel

		This constructor is used if you just want to set the colour values of the
		pixel. The alpha is set to max making the pixel fully visible. If this is not
		the transparency you want, you can use the other constructor that sets all 4
		values of the pixel.

		\param red - the r value of the pixel
		\param green - the g value of the pixel
		\param blue - the b value of the pixel
		*/
		/******************************************************************************/
		explicit constexpr Pixel ( const GLubyte red, const GLubyte green, const GLubyte blue ) noexcept : Pixel { red, green, blue, 255 }
		{
		}
		/******************************************************************************/
		/*!
		\brief
		Constructor used to set the pixel to a grayscale value plus transparency.

		This constructor is used for converting grayscale values with transparency into
		the RGBA format. It does this easily by setting the r,g and b values to the
		grayscale value respectively. If you are not interested in setting the
		transparency too, use the constructor that accepts only one grayscale value.

		\param grayscale - the grayscale value of the pixel
		\param alpha - the a value of the pixel
		*/
		/******************************************************************************/
		explicit constexpr Pixel ( const GLubyte grayscale, const GLubyte alpha ) noexcept : Pixel { grayscale, grayscale, grayscale, alpha }
		{
		}
		/******************************************************************************/
		/*!
		\brief
		Constructor used to set the pixel to a grayscale value.

		This constructor is used for converting grayscale values into the RGBA format.
		It does this easily by setting the r,g and b values to the grayscale value
		respectively. The alpha is set to max making the pixel fully visible. If this
		is not the transparency you want, you can use the other constructor that sets
		the grayscale value of the pixel plus transparency.

		\param grayscale - the grayscale value of the pixel
		*/
		/******************************************************************************/
		explicit constexpr Pixel ( const GLubyte grayscale ) noexcept : Pixel { grayscale, grayscale, grayscale, 255 }
		{
		}

		GLubyte red { };
		GLubyte green { };
		GLubyte blue { };
		GLubyte alpha { };
	};

	class Texture
	{
	public:
		class FrameBuffer
		{
		protected:
			static void AddFrameBufferTexture ( Texture& texture, const GLenum attachment, const GLint mipmap_levels );
		};

		Texture ( ) noexcept;
		explicit Texture ( const GLsizei width, const GLsizei height, const std::vector<Pixel>& pixels ) noexcept;

		Texture ( const Texture& texture ) = delete;
		Texture& operator=( const Texture& texture ) = delete;

		Texture ( Texture&& texture ) = default;
		Texture& operator=( Texture&& texture ) = default;

		bool Initialised ( ) const noexcept;

		void Bind ( ) const noexcept;

		static void SetActiveSlot ( const std::size_t slot ) noexcept;
		static void Fill ( const GLsizei width, const GLsizei height, const std::vector<Pixel>& pixels ) noexcept;
		void SetRGBAByte ( const GLsizei width, const GLsizei height ) noexcept;
		void SetRFloat ( const GLsizei width, const GLsizei height ) noexcept;
		void SetRGBFloat ( const GLsizei width, const GLsizei height ) noexcept;
		void SetRGBAFloat ( const GLsizei width, const GLsizei height ) noexcept;
		void SetDepthStencil ( const GLsizei width, const GLsizei height ) noexcept;
		void SetDepth ( const GLsizei width, const GLsizei height ) noexcept;

	private:
		class Deleter
		{
		public:
			using pointer = GLuint;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<GLuint, Deleter>;

		static GLuint CreateHandle ( ) noexcept;

		Handle handle_;
	};
}