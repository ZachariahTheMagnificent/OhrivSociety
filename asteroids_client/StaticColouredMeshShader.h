#pragma once
#include "opengl\Shader.h"
#include "math\Matrix4x4.h"
#include "Game.h"
#include "opengl\VertexBuffer.h"

class StaticColouredMeshShader : public opengl::Shader
{
public:
	static constexpr std::size_t MAX_MATERIALS = 32;
	using ClientVector3 = Game::Vector3;
	using ClientMatrix = Game::Matrix;

	enum class Attribute : GLuint
	{
		position,
		colour,
		material,
		total
	};

	class DefaultDefaultPosition
	{
	public:
		static void SetAttribute ( const GLuint attribute );
	};
	class DefaultDefaultColour
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

	class ColourEnabled
	{
	};
	template<class DefaultUv = DefaultDefaultColour>
	class ColourDisabled
	{
	};

	class MaterialEnabled
	{
	};
	template<class DefaultMaterial = DefaultDefaultMaterial>
	class MaterialDisabled
	{
	};

	template<class PositionRequirement, class ColourRequirement, class MaterialRequirement>
	class State
	{
	public:
		template<class NewPositionRequirement, class NewColourRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NewColourRequirement, NewMaterialRequirement> ( )
		{
			FufillRequirement ( NewPositionRequirement { } );
			FufillRequirement ( NewColourRequirement { } );
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
		void FufillRequirement ( ColourEnabled )
		{
			if ( !std::is_same<ColourEnabled, ColourRequirement>::value )
			{
				opengl::VertexBuffer::EnableAttribute ( colour_attribute );
			}
		}
		template<class NewDefaultColour = DefaultDefaultColour>
		void FufillRequirement ( ColourDisabled<NewDefaultColour> )
		{
			if ( std::is_same<ColourEnabled, ColourRequirement>::value )
			{
				opengl::VertexBuffer::DisableAttribute ( static_cast<GLuint>( Attribute::colour ) );
				NewDefaultColour::SetAttribute ( static_cast<GLuint>( Attribute::colour ) );
			}
			if ( !std::is_same<ColourDisabled<NewDefaultColour>, ColourRequirement> ( ) )
			{
				NewDefaultColour::SetAttribute ( static_cast<GLuint>( Attribute::colour ) );
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

		~Start ( );

		template<class NewPositionRequirement, class NewColourRequirement, class NewMaterialRequirement>
		operator State<NewPositionRequirement, NewColourRequirement, NewMaterialRequirement> ( )
		{
			return { };
		}

		template<class Func>
		auto operator<<( Func&& func )
		{
			return State<PositionDisabled<>, ColourDisabled<>, MaterialDisabled<>> {} << std::forward<Func> ( func );
		}
	};

	StaticColouredMeshShader ( );

	Start Run ( );

	void UpdateMatrices ( const ClientMatrix& client_model_view_perspective );

	std::vector<Vector<GLfloat, 4>>& GetColours ( );

	void UpdateColours ( );

private:
	Uniform<Matrix<GLfloat, 4, 4>> model_view_perspective_ { GetUniformId ( "model_view_perspective" ) };

	UniformArray<Vector<GLfloat, 4>> colours_ { GetUniformId ( "material.colour" ) };
};