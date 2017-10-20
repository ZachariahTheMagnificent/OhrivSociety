#version 330 core

// Input vertex data, different for all executions of this shader.
layout ( location = 0 ) in vec3 vertex_position_modelspace;
layout ( location = 1 ) in vec3 vertex_colour;
layout ( location = 2 ) in uint vertex_material_index;

// Output data ; will be interpolated for each fragment.
out vec3 fragment_colour;
flat out uint fragment_material_index;

// Values that stay constant for the whole mesh.
uniform mat4 model_view_perspective;

void main ( )
{
	// Output position of the vertex, in clip space : model_view_perspective * position
	gl_Position = model_view_perspective * vec4 ( vertex_position_modelspace, 1 );
	
	// The color of each vertex will be interpolated to produce the color of each fragment
	fragment_colour = vertex_colour;
	// A simple pass through. It is presumed that each vertex will have the same material index.
	fragment_material_index = vertex_material_index;

}