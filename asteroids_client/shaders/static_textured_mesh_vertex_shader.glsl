#version 330 core

// Input vertex data, different for all executions of this shader.
layout ( location = 0 ) in vec3 vertex_position_modelspace;
layout ( location = 1 ) in vec2 vertex_texture_coordinate;
layout ( location = 2 ) in uint vertex_material_index;

// Output data ; will be interpolated for each fragment.
out vec2 fragment_texture_coordinate;
flat out uint fragment_material_index;

// Values that stay constant for the whole mesh.
uniform mat4 model_view_perspective;

void main ( )
{
	// Output position of the vertex, in clip space : model_view_perspective * position
	gl_Position = model_view_perspective * vec4 ( vertex_position_modelspace, 1 );
	
	// A simple pass through. The texture_coordinate of each fragment will be interpolated from vertex_texture_coordinate of each vertex
	fragment_texture_coordinate = vertex_texture_coordinate;
	// A simple pass through. It is presumed that each vertex will have the same material index.
	fragment_material_index = vertex_material_index;

}