#version 330 core

// Interpolated values from the vertex shaders
in vec2 fragment_texture_coordinate;
flat in uint fragment_material_index;

// Output data
out vec4 colour;

// Constant values
const uint MAX_MATERIALS = 32u;

struct Material
{
	vec4 colour [ MAX_MATERIALS ];
	sampler2D colour_texture [ MAX_MATERIALS ];
};

// Values that stay constant for the whole mesh.
uniform Material material;

void main ( )
{
	colour = texture ( material.colour_texture [ fragment_material_index ], fragment_texture_coordinate ) * material.colour [ fragment_material_index ];
}