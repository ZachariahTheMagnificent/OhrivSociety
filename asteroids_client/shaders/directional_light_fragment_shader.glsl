#version 330 core

// Interpolated values from the vertex shaders
in vec2 fragment_texture_coordinate;

// Output data
out vec4 colour;

struct Light
{
	vec3 position_cameraspace;
	vec3 direction_cameraspace;
	vec3 colour;
	float power;
};

// Values that stay constant for the whole mesh.
uniform Light light;
uniform mat4 shadow_texture_matrix;
uniform sampler2D shadow_texture;
uniform sampler2D position_worldspace_texture;
uniform sampler2D position_cameraspace_texture;
uniform sampler2D normal_cameraspace_texture;
uniform sampler2D material_colour_texture;
uniform sampler2D ambient_colour_texture;
uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform sampler2D specular_focus_texture;

void main ( )
{
	// Get the values from the input textures
	vec3 position_worldspace = texture ( position_worldspace_texture, fragment_texture_coordinate ).rgb;
	vec3 position_cameraspace = texture ( position_cameraspace_texture, fragment_texture_coordinate ).rgb;
	vec3 normal_cameraspace = texture ( normal_cameraspace_texture, fragment_texture_coordinate ).rgb;
	vec4 material_colour = texture ( material_colour_texture, fragment_texture_coordinate );
	vec4 ambient_colour = texture ( ambient_colour_texture, fragment_texture_coordinate );
	vec4 diffuse = texture ( diffuse_texture, fragment_texture_coordinate );
	vec4 specular = texture ( specular_texture, fragment_texture_coordinate );
	float specular_focus = texture ( specular_focus_texture, fragment_texture_coordinate ).r;
	
	vec3 position_lightspace = ( shadow_texture_matrix * vec4 ( position_worldspace, 1 ) ).xyz;
	float shadow_depth = texture ( shadow_texture, position_lightspace.xy ).r;

	vec3 to_eye_normalized_cameraspace = -normalize ( position_cameraspace );
	
	// directional lights will always be at a specific direction from the fragment for all fragments
	vec3 fragment_to_light_direction_cameraspace = -light.direction_cameraspace;

	float cos_theta = clamp ( dot ( normal_cameraspace, fragment_to_light_direction_cameraspace ), 0, 1 );
	
	// The reflection of the light from the fragment's surface
	vec3 light_reflection = reflect ( light.direction_cameraspace, normal_cameraspace );
	float cos_alpha = clamp ( dot ( to_eye_normalized_cameraspace, light_reflection ), 0, 1 );
	
	float visibility = 0.0f;
	float bias = 0.005*tan(acos(cos_theta)); // cosTheta is dot( n,l ), clamped between 0 and 1
	bias = clamp(bias, 0,0.01);

	if ( position_lightspace.z - bias < shadow_depth )
	{
		visibility = 1.0f;
	}

	colour =
		// Diffuse : "color" of the object
		material_colour * diffuse * vec4 ( light.colour, 1 ) * light.power * cos_theta * visibility +
		
		// Specular : reflective highlight, like a mirror
		specular * vec4 ( light.colour, 1 ) * light.power * pow ( cos_alpha, specular_focus ) * visibility
		
		// Ambient : simulates lighting bouncing off surrounding objects
		+ ambient_colour;
}