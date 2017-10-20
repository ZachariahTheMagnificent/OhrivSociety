#include "Terrain.h"
#include <file_input\Targa.h>

float CubicInterpolate ( const float p1, const float p2, const float p3, const float p4, const float x )
{
	return p2 + 0.5f * x*( p3 - p1 + x*( 2.0f*p1 - 5.0f*p2 + 4.0f*p3 - p4 + x*( 3.0f*( p2 - p3 ) + p4 - p1 ) ) );
}

Terrain::Terrain ( const std::string& file_path, const unsigned resolution, const float height_multiplier ) : height_map_ { file_path }
{
	constexpr Vector3 up { 0, 1, 0 };

	Vertex vert;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	const std::size_t num_faces = resolution * resolution;
	const std::size_t vert_pitch = resolution + 1;

	vertices.reserve ( vert_pitch * vert_pitch );
	indices.reserve ( num_faces * 6 );

	{
		auto y_values = height_map_.Read ( vert_pitch, vert_pitch );

		float d_width = 1.f / resolution;
		float d_height = 1.f / resolution;

		for ( unsigned i1 = 0; i1 < resolution + 1; ++i1 )
		{
			for ( unsigned i2 = 0; i2 < resolution + 1; ++i2 )
			{
				const std::size_t ix = i2;
				const std::size_t iz = i1;

				const float x = ix * d_width;
				const float z = iz * d_height;
				const float u = x;
				const float v = z;

				const float y = y_values [ ix + iz * vert_pitch ] * height_multiplier;

				vert.position = { -0.5f + x, y, -0.5f + z };
				vert.normal = up.array ( );
				vert.uv = { u, v };
				vertices.push_back ( vert );
			}
		}
	}

	const std::size_t face_normal_pitch = resolution + 2;
	std::vector<Vector3> face_normals;
	face_normals.reserve ( face_normal_pitch * face_normal_pitch );

	for ( std::size_t i = 0; i < face_normal_pitch; ++i )
	{
		face_normals.push_back ( up );
	}
	for ( unsigned i1 = 0; i1 < resolution; ++i1 )
	{
		face_normals.push_back ( up );

		for ( unsigned i2 = 0; i2 < resolution; ++i2 )
		{
			Vector3 face_edge_1;
			Vector3 face_edge_2;

			std::size_t vert1_index;
			std::size_t vert2_index;
			std::size_t vert3_index;
			std::size_t vert4_index;

			{
				const std::size_t ix = i2;
				const std::size_t iz = i1;

				vert1_index = ix + iz * vert_pitch;

				Vector3 position { vertices [ vert1_index ].position };

				face_edge_1 = -position;
				face_edge_2 = -position;
			}

			{
				const std::size_t ix = i2 + 1;
				const std::size_t iz = i1;

				vert2_index = ix + iz * vert_pitch;

				Vector3 position { vertices [ vert2_index ].position };
				
				face_edge_2 += position;
			}

			{
				const std::size_t ix = i2 + 1;
				const std::size_t iz = i1 + 1;

				vert3_index = ix + iz * vert_pitch;

				Vector3 position { vertices [ vert3_index ].position };

				face_edge_1 += position;
			}

			{
				const std::size_t ix = i2;
				const std::size_t iz = i1 + 1;

				vert4_index = ix + iz * vert_pitch;
			}

			indices.push_back ( vert1_index );
			indices.push_back ( vert3_index );
			indices.push_back ( vert2_index );
			indices.push_back ( vert1_index );
			indices.push_back ( vert4_index );
			indices.push_back ( vert3_index );

			face_normals.push_back ( face_edge_1.Cross ( face_edge_2 ) );
		}
		face_normals.push_back ( up );
	}
	for ( std::size_t i = 0; i < face_normal_pitch; ++i )
	{
		face_normals.push_back ( up );
	}

	for ( std::size_t vertex_y = 0; vertex_y < vert_pitch; ++vertex_y )
	{
		for ( std::size_t vertex_x = 0; vertex_x < vert_pitch; ++vertex_x )
		{
			const std::size_t face1_x = vertex_x;
			const std::size_t face1_y = vertex_y;
			const std::size_t face2_x = vertex_x + 1;
			const std::size_t face2_y = vertex_y;
			const std::size_t face3_x = vertex_x + 1;
			const std::size_t face3_y = vertex_y + 1;
			const std::size_t face4_x = vertex_x;
			const std::size_t face4_y = vertex_y + 1;

			const std::size_t face1_index = face1_x + face1_y * ( resolution + 2 );
			const std::size_t face2_index = face2_x + face2_y * ( resolution + 2 );
			const std::size_t face3_index = face3_x + face3_y * ( resolution + 2 );
			const std::size_t face4_index = face4_x + face4_y * ( resolution + 2 );

			const auto normal = ( face_normals [ face1_index ] + face_normals [ face2_index ] + face_normals [ face3_index ] + face_normals [ face4_index ] ).Normalized ( );

			const std::size_t vert_index = vertex_x + vertex_y * vert_pitch;

			vertices [ vert_index ].normal = normal.array ( );
		}
	}

	vertex_buffer_.Bind ( );
	vertex_buffer_.Set ( vertices );

	index_buffer_.Bind ( );
	index_buffer_.Set ( indices );

	num_indices_ = indices.size ( );
}

Terrain::HeightMap& Terrain::GetHeightMap ( ) noexcept
{
	return height_map_;
}

const Terrain::HeightMap& Terrain::GetHeightMap ( ) const noexcept
{
	return height_map_;
}

void Terrain::BindVertex ( ) noexcept
{
	vertex_buffer_.Bind ( );
}

void Terrain::BindIndex ( ) noexcept
{
	index_buffer_.Bind ( );
}

void Terrain::SetPosition ( const GLuint position_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, position_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::position ) );
}

void Terrain::SetNormal ( const GLuint normal_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, normal_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::normal ) );
}

void Terrain::SetUv ( const GLuint uv_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, uv_id, 2, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::uv ) );
}

void Terrain::Render ( )
{
	opengl::IndexBuffer::Render ( GL_TRIANGLES, num_indices_, 0 );
}

Terrain::HeightMap::HeightMap ( const std::string & file_path )
{
	std::ifstream fileStream ( file_path, std::ios::binary );
	if ( !fileStream.is_open ( ) )
	{
		throw std::runtime_error { "Impossible to open " + file_path + ". Are you in the right directory ?\n" };
	}

	struct DataFormat
	{
		void OnReadDimensions ( const std::size_t in_size_x, const std::size_t in_size_y )
		{
			size_x = in_size_x;
			size_y = in_size_y;
			if ( size_x != size_y )
			{
				throw std::runtime_error { "Heightmap size is not squarable!" };
			}
			height_map.reserve ( size_x * size_y );
		}
		void OnReadPixels ( const std::uint8_t blue, const std::uint8_t green, const std::uint8_t red, std::uint8_t alpha )
		{
			height_map.push_back ( ( static_cast< float >( red + green + blue ) / 3.f ) / 255.f );
		}

		std::size_t size_x;
		std::size_t size_y;
		std::vector<float> height_map;
	};

	file_input::Targa<DataFormat> targa { file_path };

	size_ = targa.data_.size_x;
	splines_.resize ( size_ );
	std::vector<double> x_values;
	x_values.resize ( size_ );
	std::vector<double> y_values;
	y_values.resize ( size_ );

	std::size_t itarga = 0;

	const double delta = math::Reciprocal ( static_cast< double >( size_ ) );

	for ( auto& spline : splines_ )
	{
		double x = 0;
		for ( std::size_t i = 0; i < size_; ++i, ++itarga, x += delta )
		{
			x_values [ i ] = x;
			y_values [ i ] = targa.data_.height_map [ itarga ];
		}
		spline.set_points ( x_values, y_values );
	}
}

float Terrain::HeightMap::Read ( const float x, const float z ) const
{
	std::vector<double> z_values;
	std::vector<double> y_values;

	z_values.reserve ( size_ );
	y_values.reserve ( size_ );

	const double delta = math::Reciprocal( static_cast<double>(size_) );
	double current_z = 0.f;
	for ( const auto& spline : splines_ )
	{
		const double y_value = spline ( x );
		z_values.push_back ( current_z );
		y_values.push_back ( y_value );
		current_z += delta;
	}
	tk::spline z_spline;

	z_spline.set_points ( z_values, y_values );

	return static_cast< float >( z_spline ( z ) );
}

std::vector<float> Terrain::HeightMap::Read ( const std::size_t size_x, const std::size_t size_z ) const
{
	std::vector<tk::spline> z_splines;

	z_splines.resize ( size_x );

	const double delta_x = math::Reciprocal ( static_cast<double>( size_x ) );
	double x = 0;
	std::vector<double> z_values;
	std::vector<double> y_values;
	for ( std::size_t ix = 0; ix < size_x; ++ix )
	{
		const double delta_z = math::Reciprocal ( static_cast<double>( size_ ) );
		double z = 0.f;
		for ( const auto& spline : splines_ )
		{
			const double y_value = spline ( x );

			z_values.push_back ( z );
			y_values.push_back ( y_value );

			z += delta_z;
		}

		z_splines [ ix ].set_points ( z_values, y_values );

		z_values.clear ( );
		y_values.clear ( );
		x += delta_x;
	}

	std::vector<float> values;
	values.reserve ( size_x * size_z );

	const double delta_z = math::Reciprocal ( static_cast<double>( size_z ) );
	double z = 0.f;
	for ( std::size_t iz = 0; iz < size_z; ++iz )
	{
		for ( const auto& spline : z_splines )
		{
			const double y_value = spline ( z );
			values.push_back ( static_cast< float >( y_value ) );
		}
		z += delta_z;
	}
	return values;
}

std::size_t Terrain::HeightMap::Length ( ) const noexcept
{
	return size_;
}
