#pragma once
#include "opengl\Shader.h"

class Shader2D : public opengl::Shader
{
public:
	Shader2D ( ) : opengl::Shader { "shaders\\vertex_shader_2d.glsl", "shaders\\fragment_shader_2d.glsl" }
	{
		opengl::VertexBuffer::EnableAttribute ( 0 );
		opengl::VertexBuffer::EnableAttribute ( 3 );
		*colour_texture = 0;
		Update ( colour_texture );
	}

private:
	Uniform<int> colour_texture { GetUniformId ( "colour_texture" ) };
};