#include "ObjMesh.h"
#include "data_structure\OffsetOf.h"

ObjMesh::ObjMesh ( const std::string& file_path )
{
	struct DataFormat
	{
		void OnReadVertex ( const float x, const float y, const float z, const float u, const float v, const float nx, const float ny, const float nz )
		{
			Vertex vert;
			vert.position = { x, y, z };
			vert.normal = { nx, ny, nz };
			vert.uv = { u, v };
			vert.material_index = { 0 };
			vertices.push_back ( vert );
		}
		void OnReadIndex ( const std::size_t index )
		{
			indices.push_back ( index );
		}

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
	};

	file_input::Obj<DataFormat> obj ( file_path );

	vertex_buffer_.Bind ( );
	vertex_buffer_.Set ( obj.data_.vertices );

	index_buffer_.Bind ( );
	index_buffer_.Set ( obj.data_.indices );

	num_indices_ = obj.data_.indices.size ( );
}

void ObjMesh::BindVertex ( ) noexcept
{
	vertex_buffer_.Bind ( );
}

void ObjMesh::BindIndex ( ) noexcept
{
	index_buffer_.Bind ( );
}

void ObjMesh::SetPosition ( const GLuint position_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, position_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::position ) );
}

void ObjMesh::SetNormal ( const GLuint normal_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, normal_id, 3, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::normal ) );
}

void ObjMesh::SetUv ( const GLuint uv_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLfloat { }, uv_id, 2, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::uv ) );
}

void ObjMesh::SetMaterial ( const GLuint material_id ) noexcept
{
	opengl::VertexBuffer::SetAttribute ( GLuint { }, material_id, 1, sizeof ( Vertex ), data_structure::OffsetOf ( &Vertex::material_index ) );
}

void ObjMesh::Render ( )
{
	opengl::IndexBuffer::Render ( GL_TRIANGLES, num_indices_, 0 );
}