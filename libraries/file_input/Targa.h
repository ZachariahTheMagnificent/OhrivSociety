#pragma once
#include <fstream>
#include <vector>

namespace file_input
{
	template<class DataFormat>
	class Targa
	{
	public:
		Targa ( const std::string& file_path )				// load TGA file to memory
		{
			std::ifstream fileStream ( file_path, std::ios::binary );
			if ( !fileStream.is_open ( ) )
			{
				throw std::runtime_error { ( "Impossible to open " + file_path + ". Are you in the right directory ?\n" ).c_str ( ) };
			}

			unsigned char				header [ 18 ];									// first 6 useful header bytes
			unsigned					bytesPerPixel;								    // number of bytes per pixel in TGA gile
			unsigned					imageSize;									    // for setting memory
			std::vector<unsigned char>	data;
			unsigned					width, height;

			fileStream.read ( ( char* ) header, 18 );
			width = header [ 12 ] + header [ 13 ] * 256;
			height = header [ 14 ] + header [ 15 ] * 256;

			if ( width <= 0 ||								// is width <= 0
				height <= 0 ||								// is height <=0
				( header [ 16 ] != 8 && header [ 16 ] != 24 && header [ 16 ] != 32 ) )		// is TGA 24 or 32 Bit
			{
				throw std::runtime_error { ( "File header error: " + file_path ).c_str ( ) };
			}

			data_.OnReadDimensions ( width, height );

			bytesPerPixel = header [ 16 ] / 8;						//divide by 8 to get bytes per pixel
			imageSize = width * height * bytesPerPixel;	// calculate memory required for TGA data

			data.resize ( imageSize );
			fileStream.seekg ( 18, std::ios::beg );
			fileStream.read ( ( char * ) &data.front ( ), imageSize );
			fileStream.close ( );

			if ( header [ 16 ] == 32 )
			{
				for ( std::size_t index = 0; index < data.size ( ); index += 4 )
				{
					data_.OnReadPixels ( data [ index ], data [ index + 1 ], data [ index + 2 ], data [ index + 3 ] );
				}
			}
			else if ( header [ 16 ] == 24 )
			{
				for ( std::size_t index = 0; index < data.size ( ); index += 3 )
				{
					data_.OnReadPixels ( data [ index ], data [ index + 1 ], data [ index + 2 ], 255 );
				}
			}
			else if ( header [ 16 ] == 8 )
			{
				for ( std::size_t index = 0; index < data.size ( ); ++index )
				{
					data_.OnReadPixels ( data [ index ], data [ index ], data [ index ], 255 );
				}
			}
		}

		DataFormat data_;
	};
}