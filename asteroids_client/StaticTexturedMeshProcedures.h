#pragma once
#include "Game.h"
#include "ObjMesh.h"
#include "Sprite.h"
#include "TargaTexture.h"
#include "SkyPlane.h"
#include "Terrain.h"
#include "Image.h"
#include "StaticTexturedMeshShader.h"

class StaticTexturedMeshProcedures
{
public:
	using Matrix = Game::Matrix;

	using Shader = StaticTexturedMeshShader;
	template<class PositionRequirement, class UvRequirement, class MaterialRequirement>
	using ShaderState = Shader::State<PositionRequirement, UvRequirement, MaterialRequirement>;
	using PositionEnabled = Shader::PositionEnabled;
	using PositionDisabled = Shader::PositionDisabled<>;
	using UvEnabled = Shader::UvEnabled;
	using UvDisabled = Shader::UvDisabled<>;
	using MaterialEnabled = Shader::MaterialEnabled;
	using MaterialDisabled = Shader::MaterialDisabled<>;
	using Attribute = Shader::Attribute;

	auto Render ( Shader& shader, ObjMesh& obj, Matrix mvp )
	{
		return [ &shader, &obj, &mvp ] ( ShaderState<PositionEnabled, UvEnabled, MaterialEnabled> state )
		{
			shader.UpdateMatrices ( mvp );

			obj.BindVertex ( );
			obj.BindIndex ( );
			obj.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			obj.SetUv ( static_cast< GLuint >( Attribute::uv ) );
			obj.SetMaterial ( static_cast< GLuint >( Attribute::material ) );

			obj.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, Terrain& terrain, Matrix mvp )
	{
		return [ &shader, &terrain, &mvp ] ( ShaderState<PositionEnabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( mvp );

			terrain.BindVertex ( );
			terrain.BindIndex ( );

			terrain.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			terrain.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			terrain.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, SkyPlane& sky_plane, Matrix mvp )
	{
		return [ &shader, &sky_plane, &mvp ] ( ShaderState<PositionEnabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( mvp );

			sky_plane.BindVertex ( );
			sky_plane.BindIndex ( );

			sky_plane.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			sky_plane.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			sky_plane.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, Sprite& sprite, const Sprite::Instance& sprite_instance, Matrix mvp )
	{
		return [ &shader, &sprite, &sprite_instance, &mvp ] ( ShaderState<PositionEnabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( mvp );

			sprite.BindVertex ( );
			sprite.BindIndex ( );

			sprite.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			sprite.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			sprite.Render ( sprite_instance );

			return state;
		};
	}

	auto Render ( Shader& shader, Image& image, Matrix mvp )
	{
		return [ &shader, &image, &mvp ] ( ShaderState<PositionEnabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( mvp );

			image.BindVertex ( );
			image.BindIndex ( );

			image.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			image.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			image.Render ( );

			return state;
		};
	}
};