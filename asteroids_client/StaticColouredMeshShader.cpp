#include "StaticColouredMeshShader.h"
#include "opengl\VertexBuffer.h"

StaticColouredMeshShader::StaticColouredMeshShader ( ) : opengl::Shader { "shaders\\static_coloured_mesh_vertex_shader.glsl", "shaders\\static_coloured_mesh_fragment_shader.glsl" }
{

}

StaticColouredMeshShader::Start StaticColouredMeshShader::Run ( )
{
	return { };
}

void StaticColouredMeshShader::UpdateMatrices ( const ClientMatrix& client_model_view_perspective )
{
	*model_view_perspective_ = client_model_view_perspective;
	Update ( model_view_perspective_ );
}

std::vector<StaticColouredMeshShader::Vector<GLfloat, 4>>& StaticColouredMeshShader::GetColours ( )
{
	return colours_;
}

void StaticColouredMeshShader::UpdateColours ( )
{
	Update ( colours_ );
}

void StaticColouredMeshShader::DefaultDefaultPosition::SetAttribute ( const GLuint attribute )
{
	std::array<float, 3> arr { 0, 0, 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

void StaticColouredMeshShader::DefaultDefaultColour::SetAttribute ( const GLuint attribute )
{
	std::array<float, 3> arr { 0, 0, 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

void StaticColouredMeshShader::DefaultDefaultMaterial::SetAttribute ( const GLuint attribute )
{
	std::array<float, 1> arr { 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

StaticColouredMeshShader::Start::~Start ( )
{
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::position ) );
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::colour ) );
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::material ) );
}
