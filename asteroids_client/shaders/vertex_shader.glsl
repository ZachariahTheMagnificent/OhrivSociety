#version 330 core

// Input vertex data, different for all executions of this shader.
layout( location = 0 ) in vec3 vertex_position_modelspace;
layout( location = 1 ) in vec3 vertex_normal_modelspace;
layout( location = 2 ) in vec2 vertex_texture_coordinate;
layout( location = 3 ) in uint vertex_material_index;

// Output data ; will be interpolated for each fragment.
out vec3 fragment_position_cameraspace;
out vec3 fragment_normal_cameraspace;
out vec2 fragment_texture_coordinate;
flat out uint fragment_material_index;

// Values that stay constant for the whole mesh.
uniform mat4 model_view_perspective;
uniform mat4 model_view;
uniform mat4 model_view_inverse_transpose;

void main ( )
{
	// Output position of the vertex, in clip space : model_view_perspective * position
	gl_Position = model_view_perspective * vec4 ( vertex_position_modelspace, 1 );
	
	// Fragment position, in camera space
	fragment_position_cameraspace = ( model_view * vec4 ( vertex_position_modelspace, 1 ) ).xyz;

	// Fragment normal, in camera space
	// Use model_view_inverse_transpose if the model matrix scales the model! Otherwise, you can use model_view instead.
	fragment_normal_cameraspace = ( model_view_inverse_transpose * vec4 ( vertex_normal_modelspace, 0 ) ).xyz;

	// A simple pass through. The texture_coordinate of each fragment will be interpolated from vertex_texture_coordinate of each vertex
	fragment_texture_coordinate = vertex_texture_coordinate;

	// A simple pass through. It is presumed that each vertex will have the same material index.
	fragment_material_index = vertex_material_index;
}