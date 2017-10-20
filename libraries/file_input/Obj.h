#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

namespace file_input
{
	template<class DataFormat>
	class Obj
	{
	public:
		Obj ( const std::string& file_path )
		{
			struct Vector
			{
				constexpr Vector ( ) = default;
				constexpr explicit Vector ( const float x, const float y, const float z ) noexcept : x ( x ), y ( y ), z ( z )
				{
				}

				constexpr bool operator==( const Vector vec ) const noexcept
				{
					return x == vec.x && y == vec.y && z == vec.z;
				}

				float x { };
				float y { };
				float z { };
			};
			struct Uv
			{
				constexpr Uv ( ) = default;
				constexpr explicit Uv ( const float u, const float v ) noexcept : u ( u ), v ( v )
				{
				}

				constexpr bool operator==( const Uv uv ) const noexcept
				{
					return u == uv.u && v == uv.v;
				}

				float u { };
				float v { };
			};
			std::ifstream file_stream ( file_path, std::ios::binary );
			if ( !file_stream.is_open ( ) )
			{
				throw std::runtime_error { ( "Impossible to open " + file_path + ". Are you in the right directory ?\n" ).c_str ( ) };
			}

			std::vector<unsigned> position_indices, uv_indices, normal_indices;
			std::vector<Vector> temp_positions;
			std::vector<Uv> temp_uvs;
			std::vector<Vector> temp_normals;

			while ( !file_stream.eof ( ) )
			{
				char buf [ 256 ];
				file_stream.getline ( buf, 256 );
				if ( strncmp ( "v ", buf, 2 ) == 0 )
				{
					float position [ 3 ];
					sscanf_s ( ( buf + 2 ), "%f%f%f", position, position + 1, position + 2 );
					temp_positions.emplace_back ( position [ 0 ], position [ 1 ], position [ 2 ] );
				}
				else if ( strncmp ( "vt ", buf, 3 ) == 0 )
				{
					float tex_coord [ 2 ];
					sscanf_s ( ( buf + 2 ), "%f%f", tex_coord, tex_coord + 1 );
					temp_uvs.emplace_back ( tex_coord [ 0 ], tex_coord [ 1 ] );
				}
				else if ( strncmp ( "vn ", buf, 3 ) == 0 )
				{
					float normal [ 3 ];
					sscanf_s ( ( buf + 2 ), "%f%f%f", normal, normal + 1, normal + 2 );
					temp_normals.emplace_back ( normal [ 0 ], normal [ 1 ], normal [ 2 ] );
				}
				else if ( strncmp ( "f ", buf, 2 ) == 0 )
				{
					unsigned int vertex_index [ 4 ], uv_index [ 4 ], normal_index [ 4 ];
					int matches = sscanf_s ( ( buf + 2 ), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
						&vertex_index [ 0 ], &uv_index [ 0 ], &normal_index [ 0 ],
						&vertex_index [ 1 ], &uv_index [ 1 ], &normal_index [ 1 ],
						&vertex_index [ 2 ], &uv_index [ 2 ], &normal_index [ 2 ],
						&vertex_index [ 3 ], &uv_index [ 3 ], &normal_index [ 3 ] );

					if ( matches == 9 ) //triangle
					{
						position_indices.push_back ( vertex_index [ 0 ] );
						position_indices.push_back ( vertex_index [ 1 ] );
						position_indices.push_back ( vertex_index [ 2 ] );
						uv_indices.push_back ( uv_index [ 0 ] );
						uv_indices.push_back ( uv_index [ 1 ] );
						uv_indices.push_back ( uv_index [ 2 ] );
						normal_indices.push_back ( normal_index [ 0 ] );
						normal_indices.push_back ( normal_index [ 1 ] );
						normal_indices.push_back ( normal_index [ 2 ] );
					}
					else if ( matches == 12 ) //quad
					{
						position_indices.push_back ( vertex_index [ 0 ] );
						position_indices.push_back ( vertex_index [ 1 ] );
						position_indices.push_back ( vertex_index [ 2 ] );
						uv_indices.push_back ( uv_index [ 0 ] );
						uv_indices.push_back ( uv_index [ 1 ] );
						uv_indices.push_back ( uv_index [ 2 ] );
						normal_indices.push_back ( normal_index [ 0 ] );
						normal_indices.push_back ( normal_index [ 1 ] );
						normal_indices.push_back ( normal_index [ 2 ] );

						position_indices.push_back ( vertex_index [ 2 ] );
						position_indices.push_back ( vertex_index [ 3 ] );
						position_indices.push_back ( vertex_index [ 0 ] );
						uv_indices.push_back ( uv_index [ 2 ] );
						uv_indices.push_back ( uv_index [ 3 ] );
						uv_indices.push_back ( uv_index [ 0 ] );
						normal_indices.push_back ( normal_index [ 2 ] );
						normal_indices.push_back ( normal_index [ 3 ] );
						normal_indices.push_back ( normal_index [ 0 ] );
					}
					else
					{
						throw std::runtime_error { ( "Error line: \"" + std::string ( buf ) + "\". File can't be read by parser\n" ).c_str ( ) };
					}
				}
			}
			file_stream.close ( );

			struct Vertex
			{
				constexpr Vertex ( ) = default;
				constexpr explicit Vertex ( const Vector position, const Uv uv, const Vector normal ) noexcept : position { position }, uv { uv }, normal { normal }
				{
				}

				constexpr bool operator==( const Vertex vert ) const noexcept
				{
					return position == vert.position && uv == vert.uv && normal == vert.normal;
				}

				Vector position;
				Uv uv;
				Vector normal;
			};
			std::vector<Vertex> read_vertices;
			// For each vertex of each triangle
			for ( unsigned i = 0; i < position_indices.size ( ); ++i )
			{
				// Get the indices of its attributes
				const unsigned int position_index = position_indices [ i ] - 1;
				const unsigned int uv_index = uv_indices [ i ] - 1;
				const unsigned int normal_index = normal_indices [ i ] - 1;

				const auto position = temp_positions [ position_index ];
				const auto uv = temp_uvs [ uv_index ];
				const auto normal = temp_normals [ normal_index ];

				const Vertex vertex { position, uv, normal };

				bool found_similar = false;
				for ( std::size_t i = 0; i < read_vertices.size ( ); ++i )
				{
					if ( vertex == read_vertices [ i ] )
					{
						found_similar = true;
						// Give the index to the callback
						data_.OnReadIndex ( i );
						break;
					}
				}
				if ( !found_similar )
				{
					// Give the attributes to the callback
					data_.OnReadVertex ( vertex.position.x, vertex.position.y, vertex.position.z, vertex.uv.u, vertex.uv.v, vertex.normal.x, vertex.normal.y, vertex.normal.z );
					data_.OnReadIndex ( read_vertices.size ( ) );
					read_vertices.push_back ( vertex );
				}
			}
		}

		DataFormat data_;
	};
}