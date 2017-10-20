#version 330 core

// Input vertex data, different for all executions of this shader.
layout ( location = 0 ) in vec3 vertex_position;
layout ( location = 1 ) in vec2 vertex_texture_coordinate;

// Output data
out vec2 fragment_texture_coordinate;

void main ( )
{
	// Output position of the vertex, in clip space
	gl_Position = vec4 ( vertex_position, 1 );

	// A simple pass through. The texture_coordinate of each fragment will be interpolated from vertex_texture_coordinate of each vertex
	fragment_texture_coordinate = vertex_texture_coordinate;
}