#include "TargaTexture.h"

TargaTexture::TargaTexture ( const std::string & file_path )
{
	struct DataFormat
	{
		void OnReadDimensions ( const std::size_t in_size_x, const std::size_t in_size_y )
		{
			size_x = in_size_x;
			size_y = in_size_y;
			pixels.reserve ( size_x * size_y );
		}
		void OnReadPixels ( const std::uint8_t blue, const std::uint8_t green, const std::uint8_t red, std::uint8_t alpha )
		{
			pixels.push_back ( opengl::Pixel { red, green, blue, alpha } );
		}

		std::size_t size_x;
		std::size_t size_y;
		std::vector<opengl::Pixel> pixels;
	};

	file_input::Targa<DataFormat> targa { file_path };

	Bind ( );
	Fill ( targa.data_.size_x, targa.data_.size_y, targa.data_.pixels );
}