#include "Sprite.h"
#include <data_structure\OffsetOf.h>

Sprite::Sprite ( const std::size_t rows, const std::size_t columns, const std::size_t frame_per_second ) : total_frames_ { rows * columns }, frame_per_second_ { frame_per_second }
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	const GLfloat x_half_size = 1.f;
	const GLfloat y_half_size = x_half_size * static_cast< GLfloat >( rows ) / static_cast< GLfloat >( columns );

	const GLfloat x_start = 0.f - x_half_size;
	const GLfloat x_end = 0.f + x_half_size;
	const GLfloat y_start = 0.f - y_half_size;
	const GLfloat y_end = 0.f + y_half_size;

	const GLfloat u_diff = 1.f / columns;
	const GLfloat v_diff = 1.f / rows;

	std::size_t index_increment = 0;
	for ( std::size_t row = 0; row < rows; ++row )
	{
		for ( std::size_t column = 0; column < columns; ++column )
		{
			Vertex v;
			v.position = { x_start, y_start, 0 };
			v.uv = { column * u_diff, row * v_diff };
			vertices.push_back ( v );

			v.position = { x_end, y_start, 0 };
			v.uv = { ( column + 1 ) * u_diff, row * v_diff };
			vertices.push_back ( v );

			v.position = { x_start, y_end, 0 };
			v.uv = { column * u_diff, ( row + 1 ) * v_diff };
			vertices.push_back ( v );

			v.position = { x_end, y_end, 0 };
			v.uv = { ( column + 1 ) * u_diff, ( row + 1 ) * v_diff };
			vertices.push_back ( v );

			indices.push_back ( index_increment + 0 );
			indices.push_back ( index_increment + 1 );
			indices.push_back ( index_increment + 2 );
			indices.push_back ( index_increment + 1 );
			indices.push_back ( index_increment + 3 );
			indices.push_back ( index_increment + 2 );

			index_increment += 4;
		}
	}

	vertex_buffer_.Bind ( );
	vertex_buffer_.Set ( vertices );

	index_buffer_.Bind ( );
	index_buffer_.Set ( indices );
}

Sprite::Instance Sprite::GetInstance ( ) const noexcept
{
	return Instance { total_frames_, frame_per_second_ };
}

void Sprite::BindVertex ( ) noexcept
{
	vertex_buffer_.Bind ( );
}

void Sprite::BindIndex ( ) noexcept
{
	index_buffer_.Bind ( );
}

void Sprite::SetPosition ( const GLuint position_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, position_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::position ) );
}

void Sprite::SetUv ( const GLuint uv_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, uv_id, 2, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::uv ) );
}

void Sprite::Render ( const Instance& instance ) noexcept
{
	constexpr GLsizei vert_per_frame = 6;
	opengl::IndexBuffer::Render ( GL_TRIANGLES, vert_per_frame, vert_per_frame * instance.GetCurrentFrame ( ) );
}

Sprite::Instance::Instance ( const std::size_t total_frames, const std::size_t frame_per_second ) noexcept : total_frames_ { total_frames }, total_time_before_next_frame_ { 1.f / frame_per_second }, time_until_next_frame_ { total_time_before_next_frame_ }
{

}

void Sprite::Instance::Update ( const float delta_time ) noexcept
{
	time_until_next_frame_ -= delta_time;
	if ( time_until_next_frame_ <= 0 )
	{
		++current_frame_;
		time_until_next_frame_ = total_time_before_next_frame_;
		if ( current_frame_ >= total_frames_ )
		{
			current_frame_ = 0;
		}
	}
}

void Sprite::Instance::Reset ( ) noexcept
{
	current_frame_ = 0;
	time_until_next_frame_ = total_time_before_next_frame_;
}

std::size_t Sprite::Instance::GetCurrentFrame ( ) const noexcept
{
	return current_frame_;
}