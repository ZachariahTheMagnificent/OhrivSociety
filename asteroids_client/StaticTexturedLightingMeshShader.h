#pragma once
#include "opengl\Shader.h"
#include "opengl\VertexBuffer.h"
#include "Game.h"

class StaticTexturedLightingMeshShader : public opengl::Shader
{
public:
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

	enum class Output : GLuint
	{
		position_worldspace,
		position_cameraspace,
		normal_cameraspace,
		material_colour,
		ambient_colour,
		diffuse,
		specular,
		specular_focus,
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

	struct Material
	{
		Material ( ) = default;
		Material ( const ClientVector3 ambient, const ClientVector3 diffuse, const ClientVector3 specular, const float specular_focus, const int colour_texture ) : ambient { ambient }, diffuse { diffuse }, specular { specular }, specular_focus { specular_focus }, colour_texture { colour_texture }
		{

		}
		ClientVector3 ambient;
		ClientVector3 diffuse;
		ClientVector3 specular;
		float specular_focus { };
		int colour_texture { };
	};

	StaticTexturedLightingMeshShader ( ) : opengl::Shader { "shaders\\static_textured_lighting_mesh_vertex_shader.glsl", "shaders\\static_textured_lighting_mesh_fragment_shader.glsl" }
	{
		ambients_.resize ( MAX_MATERIALS );
		diffuses_.resize ( MAX_MATERIALS );
		speculars_.resize ( MAX_MATERIALS );
		specular_focuses_.resize ( MAX_MATERIALS );
		colour_textures_.resize ( MAX_MATERIALS );
	}

	Start Run ( )
	{
		return { };
	}

	void SetMaterial ( const std::size_t material_index, const Material& material )
	{
		ambients_ [ material_index ] = material.ambient.array ( );
		diffuses_ [ material_index ] = material.diffuse.array ( );
		speculars_ [ material_index ] = material.specular.array ( );
		specular_focuses_ [ material_index ] = material.specular_focus;
		colour_textures_ [ material_index ] = material.colour_texture;
	}

	void UpdateMaterials ( )
	{
		Update ( ambients_ );
		Update ( diffuses_ );
		Update ( speculars_ );
		Update ( specular_focuses_ );
		Update ( colour_textures_ );
	}

	void UpdateMatrices ( const ClientMatrix& model, const ClientMatrix& view, const ClientMatrix& perspective )
	{
		const auto client_model_view = view * model;
		const auto client_model_view_inverse = client_model_view.GetInverse ( );

		*model_ = model;
		Update ( model_ );

		*view_ = view;
		Update ( view_ );

		*perspective_ = perspective;
		Update ( perspective_ );

		*model_view_inverse_transpose_ = client_model_view_inverse;
		model_view_inverse_transpose_.SetTranspose ( true );
		Update ( model_view_inverse_transpose_ );
	}

private:
	Uniform<Matrix<float, 4, 4>> model_ { GetUniformId ( "model" ) };
	Uniform<Matrix<float, 4, 4>> view_ { GetUniformId ( "view" ) };
	Uniform<Matrix<float, 4, 4>> perspective_ { GetUniformId ( "perspective" ) };
	Uniform<Matrix<float, 4, 4>> model_view_inverse_transpose_ { GetUniformId ( "model_view_inverse_transpose" ) };

	UniformArray<Vector<float, 3>> ambients_ { GetUniformId ( "material.ambient" ) };
	UniformArray<Vector<float, 3>> diffuses_ { GetUniformId ( "material.diffuse" ) };
	UniformArray<Vector<float, 3>> speculars_ { GetUniformId ( "material.specular" ) };
	UniformArray<float> specular_focuses_ { GetUniformId ( "material.specular_focus" ) };
	UniformArray<int> colour_textures_ { GetUniformId ( "material.colour_texture" ) };
};