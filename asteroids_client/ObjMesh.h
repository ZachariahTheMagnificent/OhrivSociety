#pragma once
#include <string>
#include <file_input\Obj.h>
#include <opengl\VertexArray.h>
#include <opengl\VertexBuffer.h>
#include <opengl\IndexBuffer.h>
#include <array>

class ObjMesh
{
public:
	ObjMesh ( ) = default;
	ObjMesh ( const std::string& file_path );

	ObjMesh ( const ObjMesh& ) = delete;
	ObjMesh& operator=( const ObjMesh& ) = delete;

	ObjMesh ( ObjMesh&& ) = default;
	ObjMesh& operator=( ObjMesh&& ) = default;

	void BindVertex ( ) noexcept;
	void BindIndex ( ) noexcept;

	static void SetPosition ( const GLuint position_id ) noexcept;
	static void SetNormal ( const GLuint normal_id ) noexcept;
	static void SetUv ( const GLuint uv_id ) noexcept;
	static void SetMaterial ( const GLuint material_id ) noexcept;

	void Render ( );

private:
	struct Vertex
	{
		std::array<GLfloat, 3> position;
		std::array<GLfloat, 3> normal;
		std::array<GLfloat, 2> uv;
		std::array<GLfloat, 1> material_index;
	};

	opengl::VertexBuffer vertex_buffer_;
	opengl::IndexBuffer index_buffer_;

	GLuint num_indices_;
};