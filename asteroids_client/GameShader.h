#pragma once
#include "opengl\Shader.h"
#include "math\Matrix4x4.h"
#include "Game.h"

class GameShader : public opengl::Shader
{
public:
	static constexpr std::size_t MAX_LIGHTS = 8;
	static constexpr std::size_t MAX_MATERIALS = 32;
	using ClientVector3 = Game::Vector3;
	using ClientMatrix = Game::Matrix;

	enum class Attribute : GLuint
	{
		position,
		normal,
		uv,
		material,
		total
	};

	class DefaultDefaultPosition
	{
	public:
		static void SetAttribute ( const GLuint attribute )
		{
			std::array<float, 3> arr { 0, 0, 0 };
			opengl::VertexBuffer::SetAttribute ( attribute, arr );
		}
	};
	class DefaultDefaultNormal
	{
	public:
		static void SetAttribute ( const GLuint attribute )
		{
			std::array<float, 3> arr { 0, 0, 1 };
			opengl::VertexBuffer::SetAttribute ( attribute, arr );
		}
	};
	class DefaultDefaultUv
	{
	public:
		static void SetAttribute ( const GLuint attribute )
		{
			std::array<float, 2> arr { 0, 0 };
			opengl::VertexBuffer::SetAttribute ( attribute, arr );
		}
	};
	class DefaultDefaultMaterial
	{
	public:
		static void SetAttribute ( const GLuint attribute )
		{
			std::array<float, 1> arr { 0 };
			opengl::VertexBuffer::SetAttribute ( attribute, arr );
		}
	};

	class PositionEnabled
	{
	};
	template<class DefaultPosition = DefaultDefaultPosition>
	class PositionDisabled
	{
	};

	class NormalEnabled
	{
	};
	template<class DefaultUv = DefaultDefaultNormal>
	class NormalDisabled
	{
	};

	class UvEnabled
	{
	};
	template<class DefaultUv = DefaultDefaultUv>
	class UvDisabled
	{
	};

	class MaterialEnabled
	{
	};
	template<class DefaultMaterial = DefaultDefaultMaterial>
	class MaterialDisabled
	{
	};

	template<class PositionRequirement, class NormalRequirement, class UvRequirement, class MaterialRequirement>
	class State
	{
	public:
		template<class NewPositionRequirement, class NormalRequirement, class NewUvRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NormalRequirement, NewUvRequirement, NewMaterialRequirement> ( )
		{
			FufillRequirement ( NewPositionRequirement { } );
			FufillRequirement ( NormalRequirement { } );
			FufillRequirement ( NewUvRequirement { } );
			FufillRequirement ( NewMaterialRequirement { } );

			return { };
		}

		template<class Func>
		auto operator<<( Func&& func )
		{
			return func ( *this );
		}

	private:
		void FufillRequirement ( PositionEnabled )
		{
			if ( !std::is_same<PositionEnabled, PositionRequirement>::value )
			{
				opengl::VertexBuffer::EnableAttribute ( static_cast<GLuint>( Attribute::position ) );
			}
		}
		template<class NewDefaultPosition = DefaultDefaultPosition>
		void FufillRequirement ( PositionDisabled<NewDefaultPosition> )
		{
			if ( std::is_same<PositionEnabled, PositionRequirement>::value )
			{
				opengl::VertexBuffer::DisableAttribute ( static_cast<GLuint>( Attribute::position ) );
				NewDefaultPosition::SetAttribute ( static_cast<GLuint>( Attribute::position ) );
			}
			if ( !std::is_same<PositionDisabled<NewDefaultPosition>, PositionRequirement> ( ) )
			{
				NewDefaultPosition::SetAttribute ( static_cast<GLuint>( Attribute::position ) );
			}
		}
		void FufillRequirement ( NormalEnabled )
		{
			if ( !std::is_same<NormalEnabled, NormalRequirement>::value )
			{
				opengl::VertexBuffer::EnableAttribute ( static_cast<GLuint>( Attribute::normal ) );
			}
		}
		template<class NewDefaultNormal = DefaultDefaultNormal>
		void FufillRequirement ( NormalDisabled<NewDefaultNormal> )
		{
			if ( std::is_same<NormalEnabled, NormalRequirement>::value )
			{
				opengl::VertexBuffer::DisableAttribute ( static_cast<GLuint>( Attribute::normal ) );
				NewDefaultNormal::SetAttribute ( static_cast<GLuint>( Attribute::normal ) );
			}
			if ( !std::is_same<PositionDisabled<NewDefaultNormal>, NormalRequirement> ( ) )
			{
				NewDefaultNormal::SetAttribute ( static_cast<GLuint>( Attribute::normal ) );
			}
		}
		void FufillRequirement ( UvEnabled )
		{
			if ( !std::is_same<UvEnabled, UvRequirement>::value )
			{
				opengl::VertexBuffer::EnableAttribute ( static_cast<GLuint>( Attribute::uv ) );
			}
		}
		template<class NewDefaultUv = DefaultDefaultUv>
		void FufillRequirement ( UvDisabled<NewDefaultUv> )
		{
			if ( std::is_same<UvEnabled, UvRequirement>::value )
			{
				opengl::VertexBuffer::DisableAttribute ( static_cast<GLuint>( Attribute::uv ) );
				NewDefaultUv::SetAttribute ( static_cast<GLuint>( Attribute::uv ) );
			}
			if ( !std::is_same<UvDisabled<NewDefaultUv>, UvRequirement> ( ) )
			{
				NewDefaultUv::SetAttribute ( static_cast<GLuint>( Attribute::uv ) );
			}
		}
		void FufillRequirement ( MaterialEnabled )
		{
			if ( !std::is_same<MaterialEnabled, MaterialRequirement>::value )
			{
				opengl::VertexBuffer::EnableAttribute ( static_cast<GLuint>( Attribute::material ) );
			}
		}
		template<class NewDefaultMaterial = DefaultDefaultMaterial>
		void FufillRequirement ( MaterialDisabled<NewDefaultMaterial> )
		{
			if ( std::is_same<MaterialEnabled, MaterialRequirement>::value )
			{
				opengl::VertexBuffer::DisableAttribute ( static_cast<GLuint>( Attribute::material ) );
				NewDefaultMaterial::SetAttribute ( static_cast<GLuint>( Attribute::material ) );
			}
			if ( !std::is_same<MaterialDisabled<NewDefaultMaterial>, MaterialRequirement> ( ) )
			{
				NewDefaultMaterial::SetAttribute ( static_cast<GLuint>( Attribute::material ) );
			}
		}
	};

	class Start
	{
	public:
		Start ( ) = default;

		Start ( const Start& ) = delete;
		Start& operator=( const Start& ) = delete;

		void* operator new( const std::size_t size ) = delete;
		void* operator new [ ] ( const std::size_t size ) = delete;
		void operator delete( void* ) = delete;
		void operator delete [ ] ( void* ) = delete;

		~Start ( )
		{
			opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::position ) );
			opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::normal ) );
			opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::uv ) );
			opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::material ) );
		}

		template<class NewPositionRequirement, class NewNormalRequirement, class NewUvRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NewNormalRequirement, NewUvRequirement, NewMaterialRequirement> ( )
		{
			return { };
		}

		template<class Func>
		auto operator<<( Func&& func )
		{
			return State<PositionDisabled<>, NormalDisabled<>, UvDisabled<>, MaterialDisabled<>> {} << std::forward<Func> ( func );
		}
	};

	struct Light
	{
		GLuint type;
		ClientVector3 position_cameraspace;
		ClientVector3 reverse_direction_cameraspace;
		ClientVector3 colours;
		float power;
		float constant_attenuation;
		float linear_attenuation;
		float quadratic_attenuation;
		float cos_cutoff;
		float cos_inner;
		float exponent;
	};

	struct Material
	{
		ClientVector3 ambient;
		ClientVector3 diffuse;
		ClientVector3 specular;
		float shininess;
		int colour_texture;
	};

	GameShader ( ) : opengl::Shader { "shaders\\vertex_shader.glsl", "shaders\\fragment_shader.glsl" }
	{
		types_.resize ( MAX_LIGHTS );
		positions_cameraspace_.resize ( MAX_LIGHTS );
		reverse_directions_cameraspace_.resize ( MAX_LIGHTS );
		colours_.resize ( MAX_LIGHTS );
		powers_.resize ( MAX_LIGHTS );
		constant_attenuations_.resize ( MAX_LIGHTS );
		linear_attenuations_.resize ( MAX_LIGHTS );
		quadratic_attenuations_.resize ( MAX_LIGHTS );
		cos_cutoffs_.resize ( MAX_LIGHTS );
		cos_inners_.resize ( MAX_LIGHTS );
		exponents_.resize ( MAX_LIGHTS );

		ambients_.resize ( MAX_MATERIALS );
		diffuses_.resize ( MAX_MATERIALS );
		speculars_.resize ( MAX_MATERIALS );
		shininesses_.resize ( MAX_MATERIALS );
		colour_textures_.resize ( MAX_MATERIALS );
	}

	void SetNumLights ( const std::size_t num )
	{
		*num_lights_ = num;
	}

	void SetLight ( const std::size_t light_index, const Light& light )
	{
		types_ [ light_index ] = light.type;
		positions_cameraspace_ [ light_index ] = light.position_cameraspace.array ( );
		reverse_directions_cameraspace_ [ light_index ] = light.reverse_direction_cameraspace.array ( );
		colours_ [ light_index ] = light.colours.array ( );
		powers_ [ light_index ] = light.power;
		constant_attenuations_ [ light_index ] = light.constant_attenuation;
		linear_attenuations_ [ light_index ] = light.linear_attenuation;
		quadratic_attenuations_ [ light_index ] = light.quadratic_attenuation;
		cos_cutoffs_ [ light_index ] = light.cos_cutoff;
		cos_inners_ [ light_index ] = light.cos_inner;
		exponents_ [ light_index ] = light.exponent;
	}

	void SetMaterial ( const std::size_t material_index, const Material& material )
	{
		ambients_ [ material_index ] = material.ambient.array();
		diffuses_ [ material_index ] = material.diffuse.array();
		speculars_ [ material_index ] = material.specular.array();
		shininesses_ [ material_index ] = material.shininess;
		colour_textures_ [ material_index ] = material.colour_texture;
	}

	void UpdateLights ( )
	{
		Update ( types_ );
		Update ( positions_cameraspace_ );
		Update ( reverse_directions_cameraspace_ );
		Update ( colours_ );
		Update ( powers_ );
		Update ( constant_attenuations_ );
		Update ( linear_attenuations_ );
		Update ( quadratic_attenuations_ );
		Update ( cos_cutoffs_ );
		Update ( cos_inners_ );
		Update ( exponents_ );
	}

	void UpdateMaterials ( )
	{
		Update ( ambients_ );
		Update ( diffuses_ );
		Update ( speculars_ );
		Update ( shininesses_ );
		Update ( colour_textures_ );
	}

	void UpdateMatrices ( const ClientMatrix& model, const ClientMatrix& view, const ClientMatrix& perspective )
	{
		const auto client_model_view = view * model;
		const auto client_model_view_perspective = perspective * client_model_view;

		*model_view_ = client_model_view;
		Update ( model_view_ );

		*model_view_inverse_transpose_ = client_model_view.GetInverse ( );
		model_view_inverse_transpose_.SetTranspose ( true );
		Update ( model_view_inverse_transpose_ );

		*model_view_perspective_ = client_model_view_perspective;
		Update ( model_view_perspective_ );
	}

private:
	Uniform<Matrix<float, 4, 4>> model_view_perspective_ { GetUniformId ( "model_view_perspective" ) };
	Uniform<Matrix<float, 4, 4>> model_view_ { GetUniformId ( "model_view" ) };
	Uniform<Matrix<float, 4, 4>> model_view_inverse_transpose_ { GetUniformId ( "model_view_inverse_transpose" ) };

	Uniform<unsigned int> num_lights_ { GetUniformId ( "num_lights" ) };
	UniformArray<unsigned int> types_ { GetUniformId ( "light.type" ) };
	UniformArray<Vector<float, 3>> positions_cameraspace_ { GetUniformId ( "light.position_cameraspace" ) };
	UniformArray<Vector<float, 3>> reverse_directions_cameraspace_ { GetUniformId ( "light.reverse_direction_cameraspace" ) };
	UniformArray<Vector<float, 3>> colours_ { GetUniformId ( "light.colour" ) };
	UniformArray<float> powers_ { GetUniformId ( "light.power" ) };
	UniformArray<float> constant_attenuations_ { GetUniformId ( "light.constant_attenuation" ) };
	UniformArray<float> linear_attenuations_ { GetUniformId ( "light.linear_attenuation" ) };
	UniformArray<float> quadratic_attenuations_ { GetUniformId ( "light.quadratic_attenuation" ) };
	UniformArray<float> cos_cutoffs_ { GetUniformId ( "light.cos_cutoff" ) };
	UniformArray<float> cos_inners_ { GetUniformId ( "light.cos_inner" ) };
	UniformArray<float> exponents_ { GetUniformId ( "light.exponent" ) };

	UniformArray<Vector<float, 3>> ambients_ { GetUniformId ( "material.ambient" ) };
	UniformArray<Vector<float, 3>> diffuses_ { GetUniformId ( "material.diffuse" ) };
	UniformArray<Vector<float, 3>> speculars_ { GetUniformId ( "material.specular" ) };
	UniformArray<float> shininesses_ { GetUniformId ( "material.shininess" ) };
	UniformArray<int> colour_textures_ { GetUniformId ( "material.colour_texture" ) };
};