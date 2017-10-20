#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragment_position_worldspace;
in vec3 fragment_position_cameraspace;
in vec3 fragment_normal_cameraspace;
in vec2 fragment_texture_coordinate;
flat in uint fragment_material_index;

// Output data
layout ( location = 0 ) out vec4 position_worldspace;
layout ( location = 1 ) out vec4 position_cameraspace;
layout ( location = 2 ) out vec4 normal_cameraspace;
layout ( location = 3 ) out vec4 material_colour;
layout ( location = 4 ) out vec4 ambient_colour;
layout ( location = 5 ) out vec4 diffuse;
layout ( location = 6 ) out vec4 specular;
layout ( location = 7 ) out vec4 specular_focus;

// Constant values
const uint MAX_MATERIALS = 32u;

struct Material
{
	vec3 ambient [ MAX_MATERIALS ];
	vec3 diffuse [ MAX_MATERIALS ];
	vec3 specular [ MAX_MATERIALS ];
	float specular_focus [ MAX_MATERIALS ];
	sampler2D colour_texture [ MAX_MATERIALS ];
};

// Values that stay constant for the whole mesh.
uniform Material material;

void main ( )
{
	// Material properties
	material_colour = texture ( material.colour_texture [ fragment_material_index ], fragment_texture_coordinate );\
	ambient_colour = material_colour * vec4 ( material.ambient [ fragment_material_index ], 1 );
	diffuse = vec4 ( material.diffuse [ fragment_material_index ], material_colour.a );
	specular = vec4 ( material.specular [ fragment_material_index ], material_colour.a );
	specular_focus = vec4 ( material.specular_focus [ fragment_material_index ], 1, 1, material_colour.a );

	// Pass the fragment transformation values
	position_worldspace = vec4 ( fragment_position_worldspace, material_colour.a );
	position_cameraspace = vec4 ( fragment_position_cameraspace, material_colour.a );
	// Normalise normal again after interpolation to ensure unit length
	normal_cameraspace = vec4 ( normalize ( fragment_normal_cameraspace ), material_colour.a );
}