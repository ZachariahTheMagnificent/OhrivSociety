#pragma once
#include <opengl\VertexArray.h>
#include <opengl\VertexBuffer.h>
#include <opengl\IndexBuffer.h>
#include <array>

class Image
{
public:
	Image ( );

	Image ( const Image& ) = delete;
	Image& operator=( const Image& ) = delete;

	Image ( Image&& ) = default;
	Image& operator=( Image&& ) = default;

	void BindVertex ( ) noexcept;
	void BindIndex ( ) noexcept;

	static void SetPosition ( const GLuint position_id ) noexcept;
	static void SetUv ( const GLuint uv_id ) noexcept;

	void Render ( ) noexcept;

private:
	struct Vertex
	{
		std::array<GLfloat, 3> position;
		std::array<GLfloat, 2> uv;
	};

	static constexpr GLsizei total_verts = 6;

	opengl::VertexBuffer vertex_buffer_;
	opengl::IndexBuffer index_buffer_;
};