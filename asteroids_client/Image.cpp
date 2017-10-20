#include "Image.h"
#include <data_structure\OffsetOf.h>

Image::Image ( )
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	const GLfloat x_half_size = 1.f;
	const GLfloat y_half_size = 1.f;

	const GLfloat x_start = 0.f - x_half_size;
	const GLfloat x_end = 0.f + x_half_size;
	const GLfloat y_start = 0.f - y_half_size;
	const GLfloat y_end = 0.f + y_half_size;

	const GLfloat u_start = 0.f;
	const GLfloat u_end = u_start + x_half_size * 2;
	const GLfloat v_start = 0.f;
	const GLfloat v_end = v_start + y_half_size * 2;

	Vertex v;
	v.position = { x_start, y_start, 0 };
	v.uv = { u_start, v_start };
	vertices.push_back ( v );

	v.position = { x_end, y_start, 0 };
	v.uv = { x_end, v_start };
	vertices.push_back ( v );

	v.position = { x_start, y_end, 0 };
	v.uv = { u_start, y_end };
	vertices.push_back ( v );

	v.position = { x_end, y_end, 0 };
	v.uv = { x_end, y_end };
	vertices.push_back ( v );

	indices.push_back ( 0 );
	indices.push_back ( 1 );
	indices.push_back ( 2 );
	indices.push_back ( 1 );
	indices.push_back ( 3 );
	indices.push_back ( 2 );

	vertex_buffer_.Bind ( );
	vertex_buffer_.Set ( vertices );

	index_buffer_.Bind ( );
	index_buffer_.Set ( indices );
}

void Image::BindVertex ( ) noexcept
{
	vertex_buffer_.Bind ( );
}

void Image::BindIndex ( ) noexcept
{
	index_buffer_.Bind ( );
}

void Image::SetPosition ( const GLuint position_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, position_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::position ) );
}

void Image::SetUv ( const GLuint uv_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, uv_id, 2, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::uv ) );
}

void Image::Render ( ) noexcept
{
	opengl::IndexBuffer::Render ( GL_TRIANGLES, total_verts, 0 );
}