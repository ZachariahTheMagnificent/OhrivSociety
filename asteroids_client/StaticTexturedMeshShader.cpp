#include "StaticTexturedMeshShader.h"
#include "opengl\VertexBuffer.h"

StaticTexturedMeshShader::StaticTexturedMeshShader ( ) : opengl::Shader { "shaders\\static_textured_mesh_vertex_shader.glsl", "shaders\\static_textured_mesh_fragment_shader.glsl" }
{

}

StaticTexturedMeshShader::Start StaticTexturedMeshShader::Run ( )
{
	return { };
}

void StaticTexturedMeshShader::UpdateMatrices ( const ClientMatrix& client_model_view_perspective )
{
	*model_view_perspective_ = client_model_view_perspective;
	Update ( model_view_perspective_ );
}

std::vector<StaticTexturedMeshShader::Vector<GLfloat, 4>>& StaticTexturedMeshShader::GetColours ( )
{
	return colours_;
}

std::vector<GLint>& StaticTexturedMeshShader::GetTextures ( )
{
	return colour_textures_;
}

void StaticTexturedMeshShader::UpdateColours ( )
{
	Update ( colours_ );
}

void StaticTexturedMeshShader::UpdateTextures ( )
{
	Update ( colour_textures_ );
}

void StaticTexturedMeshShader::DefaultDefaultPosition::SetAttribute ( const GLuint attribute )
{
	std::array<float, 3> arr { 0, 0, 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

void StaticTexturedMeshShader::DefaultDefaultUv::SetAttribute ( const GLuint attribute )
{
	std::array<float, 2> arr { 0, 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

void StaticTexturedMeshShader::DefaultDefaultMaterial::SetAttribute ( const GLuint attribute )
{
	std::array<float, 1> arr { 0 };
	opengl::VertexBuffer::SetAttribute ( attribute, arr );
}

StaticTexturedMeshShader::Start::~Start ( )
{
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::position ) );
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::uv ) );
	opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::material ) );
}