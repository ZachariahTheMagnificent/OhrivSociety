#pragma once
#include "Game.h"
#include "Image.h"
#include "DirectionalLightShader.h"
#include "StaticTexturedLightingMeshShader.h"
#include "opengl\Texture.h"

class DirectionalLightProcedures
{
public:
	using Matrix = Game::Matrix;

	using Shader = DirectionalLightShader;
	template<class PositionRequirement, class UvRequirement>
	using ShaderState = Shader::State<PositionRequirement, UvRequirement>;
	using PositionEnabled = Shader::PositionEnabled;
	using PositionDisabled = Shader::PositionDisabled<>;
	using UvEnabled = Shader::UvEnabled;
	using UvDisabled = Shader::UvDisabled<>;
	using Attribute = Shader::Attribute;

	Matrix ToUvMatrix ( )
	{
		return
		{
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f
		};
	}

	auto Render ( Shader& shader, Image& image )
	{
		return [ &shader, &image ] ( ShaderState<PositionEnabled, UvEnabled> state )
		{
			image.BindVertex ( );
			image.BindIndex ( );

			image.SetPosition ( static_cast< GLuint >( Attribute::position ) );
			image.SetUv ( static_cast< GLuint >( Attribute::uv ) );

			image.Render ( );

			return state;
		};
	}
};