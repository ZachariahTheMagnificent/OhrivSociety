#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragment_colour;
flat in uint fragment_material_index;

// Output data
out vec4 colour;

// Constant values
const uint MAX_MATERIALS = 32u;

struct Material
{
	vec4 colour [ MAX_MATERIALS ];
};

// Values that stay constant for the whole mesh.
uniform Material material;

void main ( )
{
	colour = vec4 ( fragment_colour, 1 ) * material.colour [ fragment_material_index ];
}