#pragma once
#include <string>
#include <file_input\Obj.h>
#include <opengl\VertexArray.h>
#include <opengl\VertexBuffer.h>
#include <opengl\IndexBuffer.h>
#include <array>

class SkyPlane
{
public:
	SkyPlane ( ) = default;
	explicit SkyPlane ( const std::size_t slices, const float planet_radius, const float atmosphere_radius, const float h_tile, const float v_tile );

	SkyPlane ( const SkyPlane& ) = delete;
	SkyPlane& operator=( const SkyPlane& ) = delete;

	SkyPlane ( SkyPlane&& ) = default;
	SkyPlane& operator=( SkyPlane&& ) = default;

	void BindVertex ( ) noexcept;
	void BindIndex ( ) noexcept;

	static void SetPosition ( const GLuint position_id ) noexcept;
	static void SetUv ( const GLuint uv_id ) noexcept;

	void Render ( );

private:
	struct Vertex
	{
		std::array<GLfloat, 3> position;
		std::array<GLfloat, 3> normal;
		std::array<GLfloat, 2> uv;
	};

	opengl::VertexBuffer vertex_buffer_;
	opengl::IndexBuffer index_buffer_;

	GLuint num_indices_;
};