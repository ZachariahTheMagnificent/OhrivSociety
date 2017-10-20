#pragma once
#include "Game.h"
#include "ObjMesh.h"
#include "Sprite.h"
#include "TargaTexture.h"
#include "SkyPlane.h"
#include "Terrain.h"
#include "Image.h"
#include "StaticTexturedLightingMeshShader.h"

class StaticTexturedLightingMeshProcedures
{
public:
	using Matrix = Game::Matrix;

	using Shader = StaticTexturedLightingMeshShader;
	template<class PositionRequirement, class NormalRequirement, class UvRequirement, class MaterialRequirement>
	using ShaderState = Shader::State<PositionRequirement, NormalRequirement, UvRequirement, MaterialRequirement>;
	using PositionEnabled = Shader::PositionEnabled;
	using PositionDisabled = Shader::PositionDisabled<>;
	using NormalEnabled = Shader::NormalEnabled;
	using NormalDisabled = Shader::NormalDisabled<>;
	using UvEnabled = Shader::UvEnabled;
	using UvDisabled = Shader::UvDisabled<>;
	using MaterialEnabled = Shader::MaterialEnabled;
	using MaterialDisabled = Shader::MaterialDisabled<>;
	using Attribute = Shader::Attribute;

	auto Render ( Shader& shader, ObjMesh& obj, Matrix model, Matrix view, Matrix perspective )
	{
		return [ &shader, &obj, &model, &view, &perspective ] ( ShaderState<PositionEnabled, NormalEnabled, UvEnabled, MaterialEnabled> state )
		{
			shader.UpdateMatrices ( model, view, perspective );

			obj.BindVertex ( );
			obj.BindIndex ( );

			obj.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			obj.SetNormal ( static_cast< GLuint >( Attribute::normal ) );
			obj.SetUv ( static_cast< GLuint >( Attribute::uv ) );
			obj.SetMaterial ( static_cast< GLuint >( Attribute::material ) );

			obj.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, Terrain& terrain, Matrix model, Matrix view, Matrix perspective )
	{
		return [ &shader, &terrain, &model, &view, &perspective ] ( ShaderState<PositionEnabled, NormalEnabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( model, view, perspective );

			terrain.BindVertex ( );
			terrain.BindIndex ( );

			terrain.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			terrain.SetNormal ( static_cast< GLuint >( Attribute::normal ) );
			terrain.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			terrain.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, SkyPlane& sky_plane, Matrix model, Matrix view, Matrix perspective )
	{
		return [ &shader, &sky_plane, &model, &view, &perspective ] ( ShaderState<PositionEnabled, NormalDisabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( model, view, perspective );

			sky_plane.BindVertex ( );
			sky_plane.BindIndex ( );

			sky_plane.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			sky_plane.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			sky_plane.Render ( );

			return state;
		};
	}

	auto Render ( Shader& shader, Sprite& sprite, const Sprite::Instance& sprite_instance, Matrix model, Matrix view, Matrix perspective )
	{
		return [ &shader, &sprite, &sprite_instance, &model, &view, &perspective ] ( ShaderState<PositionEnabled, NormalDisabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( model, view, perspective );

			sprite.BindVertex ( );
			sprite.BindIndex ( );

			sprite.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			sprite.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			sprite.Render ( sprite_instance );

			return state;
		};
	}

	auto Render ( Shader& shader, Image& image, Matrix model, Matrix view, Matrix perspective )
	{
		return [ &shader, &image, &model, &view, &perspective ] ( ShaderState<PositionEnabled, NormalDisabled, UvEnabled, MaterialDisabled> state )
		{
			shader.UpdateMatrices ( model, view, perspective );

			image.BindVertex ( );
			image.BindIndex ( );

			image.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			image.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			image.Render ( );

			return state;
		};
	}
};