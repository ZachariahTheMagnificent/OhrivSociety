#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragment_position_cameraspace;
in vec3 fragment_normal_cameraspace;
in vec2 fragment_texture_coordinate;
flat in uint fragment_material_index;

// Output data
out vec4 colour;

// Constant values
const uint MAX_LIGHTS = 8u;
const uint POINT_LIGHT = 0u;
const uint DIRECTIONAL_LIGHT = 1u;
const uint SPOT_LIGHT = 2u;

const uint MAX_MATERIALS = 32u;

struct Light
{
	uint type [ MAX_LIGHTS ];
	vec3 position_cameraspace [ MAX_LIGHTS ];
	vec3 reverse_direction_cameraspace [ MAX_LIGHTS ];
	vec3 colour [ MAX_LIGHTS];
	float power [ MAX_LIGHTS];
	float constant_attenuation [ MAX_LIGHTS ];
	float linear_attenuation [ MAX_LIGHTS ];
	float quadratic_attenuation [ MAX_LIGHTS ];
	float cos_cutoff [ MAX_LIGHTS ];
	float cos_inner [ MAX_LIGHTS ];
	float exponent [ MAX_LIGHTS ];
};

struct Material
{
	vec3 ambient [ MAX_MATERIALS ];
	vec3 diffuse [ MAX_MATERIALS ];
	vec3 specular [ MAX_MATERIALS ];
	float shininess [ MAX_MATERIALS ];
	sampler2D colour_texture [ MAX_MATERIALS ];
};

// Values that stay constant for the whole mesh.
uniform Light light;
uniform Material material;

float GetAttenuation ( uint light_index, float distance )
{
	return 1 / max ( 1, light.constant_attenuation [ light_index ] + light.linear_attenuation [ light_index ] * distance + light.quadratic_attenuation [ light_index ] * distance * distance );
}

float GetSpotlightEffect ( uint light_index, vec3 fragment_to_light_direction_cameraspace )
{
	float cos_fragment_to_light = dot ( fragment_to_light_direction_cameraspace, light.reverse_direction_cameraspace [ light_index ] );
	//return smoothstep ( light.cos_cutoff [ light_index ], light.cos_inner [ light_index ], cos_fragment_to_light );
	if ( cos_fragment_to_light < light.cos_cutoff [ light_index ] )
	{
		return 0;
	}
	else
	{
		return 1; //pow ( cos_fragment_to_light, light.exponent [ light_index ] );
	}
}

void main ( )
{
	// Material properties
	vec4 material_colour = texture ( material.colour_texture [ fragment_material_index ], fragment_texture_coordinate );

	// direction from fragment to eye
	vec3 fragment_to_eye_direction_cameraspace = normalize ( -fragment_position_cameraspace );
	// normalise normal again after interpolation to ensure unit length
	vec3 proper_fragment_normal_cameraspace = normalize ( fragment_normal_cameraspace );
	
	// Ambient : simulates indirect lighting
	colour = material_colour * vec4 ( material.ambient [ fragment_material_index ], 1 );
	
	for ( uint i = 0u; i < num_lights; ++i )
	{
		// Light direction
		float spotlight_effect = 1;
		// Light attenuation
		float attenuation_factor = 1;
		vec3 fragment_to_light_direction_cameraspace;
		if ( light.type [ i ] == DIRECTIONAL_LIGHT )
		{
			// directional lights will always be at a specific direction from the fragment for all fragments
			fragment_to_light_direction_cameraspace = light.reverse_direction_cameraspace [ i ];
		}
		else if ( light.type [ i ] == SPOT_LIGHT )
		{
			// Vector from fragment to light
			vec3 fragment_to_light_cameraspace = light.position_cameraspace [ i ] - fragment_position_cameraspace;
			// Distance to the light
			float fragment_to_light_distance = length ( fragment_to_light_cameraspace );
			attenuation_factor = GetAttenuation ( i, fragment_to_light_distance );
			fragment_to_light_direction_cameraspace = normalize ( fragment_to_light_cameraspace );
			spotlight_effect = GetSpotlightEffect ( i, fragment_to_light_direction_cameraspace );
		}
		else
		{
			// Vector from fragment to light
			vec3 fragment_to_light_cameraspace = light.position_cameraspace [ i ] - fragment_position_cameraspace;
			// Distance to the light
			float fragment_to_light_distance = length ( fragment_to_light_cameraspace );
			attenuation_factor = GetAttenuation ( i, fragment_to_light_distance );
			fragment_to_light_direction_cameraspace = normalize ( fragment_to_light_cameraspace );
		}

		float cos_theta = clamp ( dot ( proper_fragment_normal_cameraspace, fragment_to_light_direction_cameraspace ), 0, 1 );
		
		// The reflection of the light from the fragment's surface
		vec3 light_reflection = reflect ( -fragment_to_light_direction_cameraspace, proper_fragment_normal_cameraspace );
		float cos_alpha = clamp ( dot ( fragment_to_eye_direction_cameraspace, light_reflection ), 0, 1 );
		
		colour +=
			// Diffuse : "color" of the object
			material_colour * vec4 ( material.diffuse [ fragment_material_index ], 1 ) * vec4 ( light.colour [ i ], 1 ) * light.power [ i ] * cos_theta * attenuation_factor * spotlight_effect +
			
			// Specular : reflective highlight, like a mirror
			vec4 ( material.specular [ fragment_material_index ], 1 ) * vec4 ( light.colour [ i ], 1 ) * light.power [ i ] * pow ( cos_alpha, material.shininess [ fragment_material_index ] ) * attenuation_factor * spotlight_effect;
	}
}