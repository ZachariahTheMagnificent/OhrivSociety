#include "SkyPlane.h"
#include <data_structure\OffsetOf.h>
#include <math\Basic.h>

SkyPlane::SkyPlane ( const std::size_t slices, const float planet_radius, const float atmosphere_radius, const float h_tile, const float v_tile )
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	if ( atmosphere_radius <= planet_radius || math::AlmostEquals ( atmosphere_radius, 0.0f ) )
	{
		throw math::DivideByZero { };
	}

	const GLfloat half_plane_size = std::sqrt ( atmosphere_radius * atmosphere_radius - planet_radius * planet_radius );
	const GLfloat plane_size = 2 * half_plane_size;

	const GLfloat slice_size = plane_size / slices;
	const GLfloat slice_coord_size = 1.0f / slices;

	for ( unsigned z = 0; z <= slices; ++z )
	{
		for ( unsigned x = 0; x <= slices; ++x )
		{
			const GLfloat x_position = -half_plane_size + x * slice_size;
			const GLfloat z_position = -half_plane_size + z * slice_size;

			const GLfloat height = atmosphere_radius - ( x_position * x_position + z_position * z_position ) / atmosphere_radius;

			const GLfloat u_coord = 0 + x * slice_coord_size;
			const GLfloat v_coord = 0 + z * slice_coord_size;

			Vertex v;
			v.position = { x_position, height, z_position };
			v.normal = { 0, 0, 1 };
			v.uv = { u_coord * h_tile, v_coord * v_tile };

			vertices.push_back ( v );
		}
	}

	const GLuint verts_per_row = slices + 1;

	for ( GLuint row = 0; row < slices; ++row )
	{
		for ( GLuint column = 0; column < slices; ++column )
		{
			const GLuint start = row * verts_per_row + column;

			//triangle 1
			indices.push_back ( start );
			indices.push_back ( start + 1 );
			indices.push_back ( start + verts_per_row + 1 );

			//triangle 2
			indices.push_back ( start + verts_per_row );
			indices.push_back ( start );
			indices.push_back ( start + verts_per_row + 1 );
		}
	}

	vertex_buffer_.Bind ( );
	vertex_buffer_.Set ( vertices );

	index_buffer_.Bind ( );
	index_buffer_.Set ( indices );

	num_indices_ = indices.size ( );
}

void SkyPlane::BindVertex ( ) noexcept
{
	vertex_buffer_.Bind ( );
}

void SkyPlane::BindIndex ( ) noexcept
{
	index_buffer_.Bind ( );
}

void SkyPlane::SetPosition ( const GLuint position_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, position_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::position ) );
}

void SkyPlane::SetUv ( const GLuint uv_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, uv_id, 2, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::uv ) );
}

void SkyPlane::Render ( )
{
	opengl::IndexBuffer::Render ( GL_TRIANGLES, num_indices_, 0 );
}