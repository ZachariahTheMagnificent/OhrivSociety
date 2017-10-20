#pragma once
#include "opengl\Shader.h"
#include "opengl\VertexBuffer.h"
#include "math\Matrix4x4.h"
#include "Game.h"

class DirectionalLightShader : public opengl::Shader
{
public:
	using ClientVector3 = Game::Vector3;
	using Normal = ClientVector3::Normal;
	using ClientMatrix = Game::Matrix;

	enum class Attribute : GLuint
	{
		position,
		uv,
		totals
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
	class DefaultDefaultUv
	{
	public:
		static void SetAttribute ( const GLuint attribute )
		{
			std::array<float, 2> arr { 0, 0 };
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

	class UvEnabled
	{
	};
	template<class DefaultUv = DefaultDefaultUv>
	class UvDisabled
	{
	};

	template<class PositionRequirement, class UvRequirement>
	class State
	{
	public:
		template<class NewPositionRequirement, class NewUvRequirement>
		operator State<NewPositionRequirement, NewUvRequirement> ( )
		{
			FufillRequirement ( NewPositionRequirement { } );
			FufillRequirement ( NewUvRequirement { } );

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
			opengl::VertexBuffer::DisableAttribute ( static_cast< GLuint >( Attribute::uv ) );
		}

		template<class NewPositionRequirement, class NewUvRequirement>
		operator State<NewPositionRequirement, NewUvRequirement> ( )
		{
			return { };
		}

		template<class Func>
		auto operator<<( Func&& func )
		{
			return State<PositionDisabled<>, UvDisabled<>> {} << std::forward<Func> ( func );
		}
	};

	struct Light
	{
		Light ( ) = default;
		Light ( const Normal direction_cameraspace, const ClientVector3 colour, const float power ) : direction_cameraspace { direction_cameraspace }, colour { colour }, power { power }
		{

		}

		Normal direction_cameraspace;
		ClientVector3 colour;
		float power { };
	};

	DirectionalLightShader ( ) : opengl::Shader { "shaders\\directional_light_vertex_shader.glsl", "shaders\\directional_light_fragment_shader.glsl" }
	{
	}

	Start Run ( )
	{
		return { };
	}

	void UpdateLight ( const Light& light )
	{
		*direction_cameraspace_ = light.direction_cameraspace.array ( );
		*colour_ = light.colour.array ( );
		*power_ = light.power;

		Update ( direction_cameraspace_ );
		Update ( colour_ );
		Update ( power_ );
	}

	void UpdateShadowTextureMatrix ( const ClientMatrix& matrix )
	{
		*shadow_texture_matrix_ = matrix;
		Update ( shadow_texture_matrix_ );
	}

	void UpdateShadowTexture ( const GLint slot )
	{
		*shadow_texture_ = slot;
		Update ( shadow_texture_ );
	}

	void UpdatePositionWorldspaceTexture ( const GLint slot )
	{
		*position_worldspace_texture_ = slot;
		Update ( position_worldspace_texture_ );
	}

	void UpdatePositionCameraspaceTexture ( const GLint slot )
	{
		*position_cameraspace_texture_ = slot;
		Update ( position_cameraspace_texture_ );
	}

	void UpdateNormalCameraspaceTexture ( const GLint slot )
	{
		*normal_cameraspace_texture_ = slot;
		Update ( normal_cameraspace_texture_ );
	}

	void UpdateMaterialColourTexture ( const GLint slot )
	{
		*material_colour_texture_ = slot;
		Update ( material_colour_texture_ );
	}

	void UpdateAmbientColourTexture ( const GLint slot )
	{
		*ambient_colour_texture_ = slot;
		Update ( ambient_colour_texture_ );
	}

	void UpdateDiffuseTexture ( const GLint slot )
	{
		*diffuse_texture_ = slot;
		Update ( diffuse_texture_ );
	}

	void UpdateSpecularTexture ( const GLint slot )
	{
		*specular_texture_ = slot;
		Update ( specular_texture_ );
	}

	void UpdateSpecularFocusTexture ( const GLint slot )
	{
		*specular_focus_texture_ = slot;
		Update ( specular_focus_texture_ );
	}

private:
	Uniform<Vector<float, 3>> direction_cameraspace_ { GetUniformId ( "light.direction_cameraspace" ) };
	Uniform<Vector<float, 3>> colour_ { GetUniformId ( "light.colour" ) };
	Uniform<float> power_ { GetUniformId ( "light.power" ) };

	Uniform<Matrix<float, 4, 4>> shadow_texture_matrix_ { GetUniformId ( "shadow_texture_matrix" ) };

	Uniform<GLint> shadow_texture_ { GetUniformId ( "shadow_texture" ) };
	Uniform<GLint> position_worldspace_texture_ { GetUniformId ( "position_worldspace_texture" ) };
	Uniform<GLint> position_cameraspace_texture_ { GetUniformId ( "position_cameraspace_texture" ) };
	Uniform<GLint> normal_cameraspace_texture_ { GetUniformId ( "normal_cameraspace_texture" ) };
	Uniform<GLint> material_colour_texture_ { GetUniformId ( "material_colour_texture" ) };
	Uniform<GLint> ambient_colour_texture_ { GetUniformId ( "ambient_colour_texture" ) };
	Uniform<GLint> diffuse_texture_ { GetUniformId ( "diffuse_texture" ) };
	Uniform<GLint> specular_texture_ { GetUniformId ( "specular_texture" ) };
	Uniform<GLint> specular_focus_texture_ { GetUniformId ( "specular_focus_texture" ) };
};