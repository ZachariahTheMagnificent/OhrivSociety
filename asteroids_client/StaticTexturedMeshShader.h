#pragma once
#include "opengl\Shader.h"
#include "math\Matrix4x4.h"
#include "Game.h"
#include "opengl\VertexBuffer.h"

class StaticTexturedMeshShader : public opengl::Shader
{
public:
	static constexpr std::size_t MAX_MATERIALS = 32;
	using ClientVector3 = Game::Vector3;
	using ClientMatrix = Game::Matrix;


	enum class Attribute : GLuint
	{
		position,
		uv,
		material,
		total
	};

	class DefaultDefaultPosition
	{
	public:
		static void SetAttribute ( const GLuint attribute );
	};
	class DefaultDefaultUv
	{
	public:
		static void SetAttribute ( const GLuint attribute );
	};
	class DefaultDefaultMaterial
	{
	public:
		static void SetAttribute ( const GLuint attribute );
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

	class MaterialEnabled
	{
	};
	template<class DefaultMaterial = DefaultDefaultMaterial>
	class MaterialDisabled
	{
	};

	template<class PositionRequirement, class UvRequirement, class MaterialRequirement>
	class State
	{
	public:
		template<class NewPositionRequirement, class NewUvRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NewUvRequirement, NewMaterialRequirement> ( )
		{
			FufillRequirement ( NewPositionRequirement { } );
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
		void operator delete[]( void* ) = delete;

		~Start ( );

		template<class NewPositionRequirement, class NewUvRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NewUvRequirement, NewMaterialRequirement> ( )
		{
			return { };
		}

		template<class Func>
		auto operator<<( Func&& func )
		{
			return State<PositionDisabled<>, UvDisabled<>, MaterialDisabled<>> {} << std::forward<Func> ( func );
		}
	};

	StaticTexturedMeshShader ( );

	Start Run ( );

	void UpdateMatrices ( const ClientMatrix& client_model_view_perspective );

	std::vector<Vector<GLfloat, 4>>& GetColours ( );
	std::vector<GLint>& GetTextures ( );

	void UpdateColours ( );
	void UpdateTextures ( );

private:
	Uniform<Matrix<GLfloat, 4, 4>> model_view_perspective_ { GetUniformId ( "model_view_perspective" ) };

	UniformArray<Vector<GLfloat, 4>> colours_ { GetUniformId ( "material.colour" ) };
	UniformArray<GLint> colour_textures_ { GetUniformId ( "material.colour_texture" ) };
};