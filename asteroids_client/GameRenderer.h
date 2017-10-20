#pragma once
#include "opengl\Renderer.h"
#include "Game.h"
#include "GameShader.h"
#include "ObjMesh.h"
#include "Sprite.h"
#include "TargaTexture.h"
#include "SkyPlane.h"
#include "Terrain.h"
#include "Image.h"
#include "StaticColouredMeshShader.h"
#include "StaticTexturedMeshShader.h"
#include "StaticTexturedLightingMeshShader.h"
#include "DirectionalLightShader.h"
#include "opengl\FrameBuffer.h"
#include "StaticColouredMeshProcedures.h"
#include "StaticTexturedMeshProcedures.h"
#include "StaticTexturedLightingMeshProcedures.h"
#include "DirectionalLightProcedures.h"

class GameRenderer : public opengl::Renderer, public Game::Renderer<GameRenderer>, public StaticColouredMeshProcedures, public StaticTexturedMeshProcedures, public StaticTexturedLightingMeshProcedures, public DirectionalLightProcedures
{
public:
	using Vector3 = StaticTexturedMeshShader::ClientVector3;
	using Matrix = StaticTexturedMeshShader::ClientMatrix;
	using Rotation = Game::Rotation;

	using LightingMaterial = StaticTexturedLightingMeshShader::Material;

	using StaticColouredMeshProcedures::Render;
	using StaticTexturedMeshProcedures::Render;
	using StaticTexturedLightingMeshProcedures::Render;
	using DirectionalLightProcedures::Render;

	GameRenderer ( )
	{
		Enable<FEATURE::CULL> ( );
		Enable<FEATURE::DEPTH> ( );
		Enable<FEATURE::BLENDING> ( );

		SetClearColour ( 0.f, 0.f, 1.f, 0.f );

		arr_.Bind ( );

		{
			static_coloured_mesh_shader_.Use ( );
			auto& colours = static_coloured_mesh_shader_.GetColours ( );
			colours.resize ( 1 );
			colours [ 0 ] = { 1, 1, 1, 1 };
			static_textured_mesh_shader_.UpdateColours ( );
		}

		{
			static_textured_mesh_shader_.Use ( );

			auto& colours = static_textured_mesh_shader_.GetColours ( );
			colours.resize ( 1 );
			colours [ 0 ] = { 1, 1, 1, 1 };
			static_textured_mesh_shader_.UpdateColours ( );

			auto& textures = static_textured_mesh_shader_.GetTextures ( );
			textures.resize ( 1 );
			textures [ 0 ] = 0;
			static_textured_mesh_shader_.UpdateTextures ( );
		}

		{
			static_textured_lighting_mesh_shader_.Use ( );
		}

		{
			directional_light_shader_.Use ( );
		}

		GLint view_port [ 4 ];
		GetViewPort ( view_port );

		SetViewProperties ( view_port [ 0 ], view_port [ 1 ], view_port [ 2 ], view_port [ 3 ] );
	}

	GameRenderer ( const GameRenderer& ) = delete;
	GameRenderer& operator=( const GameRenderer& ) = delete;

	GameRenderer ( GameRenderer&& ) = default;
	GameRenderer& operator=( GameRenderer&& ) = default;

	void SetViewProperties ( const GLint bottom_left_x, const GLint bottom_left_y, const GLsizei width, const GLsizei height ) noexcept
	{
		viewport_start_x = bottom_left_x;
		viewport_start_y = bottom_left_y;
		viewport_size_x = width;
		viewport_size_y = height;

		lighting_geometry_frame_buffer.Bind ( );
		lighting_geometry_frame_buffer.SetTextures ( LightingGeometryFrameBufferSetter { viewport_size_x, viewport_size_y } );
	}

private:
	auto RenderShadowScene ( const Matrix& directional_light_matrix ) noexcept
	{
		return [ this, &directional_light_matrix ] ( auto shader )
		{
			return shader << [ this, &directional_light_matrix ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 0, -130, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 0.f } ) * Matrix::GetScale ( Vector3 { 4000, 4000, 4000 } );
				return shader << Render ( static_coloured_mesh_shader_, terrain, directional_light_matrix * model );
			}
			<< [ this, &directional_light_matrix ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 0, 37, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 0.f } ) * Matrix::GetScale ( Vector3 { 1, 1, 1 } );
				return shader << Render ( static_coloured_mesh_shader_, masterchief, directional_light_matrix * model );
			}
			<< [ this, &directional_light_matrix ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 20, 32.79f, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 180.f } ) * Matrix::GetScale ( Vector3 { 1, 1, 1 } );
				return shader << Render ( static_coloured_mesh_shader_, raigon, directional_light_matrix * model );
			};
		};
	}

	auto RenderLightingScene ( const std::vector<Vector3>& particles ) noexcept
	{
		return [ this, &particles ] ( auto shader )
		{
			Vector3 ambient { 0.1f,0.1f,0.1f };
			Vector3 diffuse { 1.f,1.f,1.f };
			Vector3 specular { 1.f,1.f,1.f };
			float specular_focus = 32.f;
			int texture = 0;
			static_textured_lighting_mesh_shader_.SetMaterial ( 0, LightingMaterial { ambient, diffuse, specular, specular_focus, texture } );
			static_textured_lighting_mesh_shader_.UpdateMaterials ( );

			return shader << [ this ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 0, -130, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 0.f } ) * Matrix::GetScale ( Vector3 { 4000, 4000, 4000 } );
				terrain_texture.Bind ( );
				return shader << Render ( static_textured_lighting_mesh_shader_, terrain, model, view_, perspective_ );
			}
			<< [ this ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 0, 37, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 0.f } ) * Matrix::GetScale ( Vector3 { 1, 1, 1 } );
				masterchief_texture.Bind ( );
				return shader << Render ( static_textured_lighting_mesh_shader_, masterchief, model, view_, perspective_ );
			}
			<< [ this ] ( auto shader )
			{
				Matrix model = Matrix::GetTranslation ( Vector3 { 20, 32.79f, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, 180.f } ) * Matrix::GetScale ( Vector3 { 1, 1, 1 } );
				raigon_texture.Bind ( );
				return shader << Render ( static_textured_lighting_mesh_shader_, raigon, model, view_, perspective_ );
			}
			<< [ this ] ( auto shader )
			{
				Vector3 ambient { 1.f,1.f,1.f };
				Vector3 diffuse { 0.f,0.f,0.f };
				Vector3 specular { 0.f,0.f,0.f };
				float specular_focus = 32.f;
				int texture = 0;
				static_textured_lighting_mesh_shader_.SetMaterial ( 0, LightingMaterial { ambient, diffuse, specular, specular_focus, texture } );
				static_textured_lighting_mesh_shader_.UpdateMaterials ( );

				Matrix model = Matrix::GetTranslation ( Vector3 { 0, -250, 0 } ) * Matrix::GetRotation ( Rotation { Vector3 { 0.f, 1.f, 0.f }, math::Pi<float>()/2 } ) * Matrix::GetScale ( Vector3 { 1, 1, 1 } );
				sky_texture.Bind ( );
				return shader << Render ( static_textured_lighting_mesh_shader_, sky_plane, model, view_, perspective_ );
			}
			<< [ this, &particles ] ( auto shader )
			{
				Matrix model;
				for ( auto& particle : particles )
				{
					model = Matrix::GetTranslation ( particle ) * Matrix::GetRotation ( Rotation { look_direction_, Vector3 { 0,0,-1 } } ) * Matrix::GetScale ( Vector3 { 10, 10, 10 } );
					snowflake_texture.Bind ( );
					Render ( static_textured_lighting_mesh_shader_, image, model, view_, perspective_ ) ( shader );
				}
				return shader << Render ( static_textured_lighting_mesh_shader_, sprite, sprite_instance, model, view_, perspective_ );
			};
		};
	}

public:
	void Render ( const Game& game )
	{
		Game::Renderer<GameRenderer>::Render ( game );

		perspective_ = Matrix::GetPerspective ( 45.0f, 800.f / 600.f, 0.1f, 10000.0f );
		//perspective_ = Matrix::GetOrtho ( -100, 100, -100, 100, -100, 100 );

		const Matrix perspective_directional_light = Matrix::GetOrtho ( -2290, 2284, -300, 300, -1000, 1000 );
		const Matrix view_directional_light = Matrix::GetViewTransform ( Vector3 { 0, 0, 0 }, direction_light_direction.Normalized ( ), Vector3 { 0, 1, 0 }.Normalized ( ) );
		const Matrix directional_light_matrix = perspective_directional_light * view_directional_light;

		directional_light_shader_.UpdateLight ( DirectionalLightShader::Light { ( view_.GetInverse ( ).Transpose ( ) * direction_light_direction.Normalized ( ) ).Normalized ( ), direction_light_colour, direction_light_power } );

		shadow_frame_buffer.Bind ( );

		glCullFace ( GL_FRONT );
		static_coloured_mesh_shader_.Use ( );
		static_coloured_mesh_shader_.Run ( )
		<< [ this, &directional_light_matrix ] ( auto shader )
		{
			SetViewPort ( 0, 0, shadow_texture_size_x, shadow_texture_size_y );

			Clear<true, true> ( );

			return shader << RenderShadowScene ( directional_light_matrix );
		};
		glCullFace ( GL_BACK );

		lighting_geometry_frame_buffer.Bind ( );

		static_textured_lighting_mesh_shader_.Use ( );
		static_textured_lighting_mesh_shader_.Run ( )
		<< [ this, &game ] ( auto shader )
		{
			SetViewPort ( 0, 0, viewport_size_x, viewport_size_y );

			Clear<true, true> ( );

			TargaTexture::SetActiveSlot ( 0 );
			
			return shader << RenderLightingScene ( game.particles_ );
		};

		lighting_geometry_frame_buffer.UnBind ( );

		directional_light_shader_.Use ( );
		directional_light_shader_.Run ( )
		<< [ this, &directional_light_matrix ] ( auto shader )
		{
			SetViewPort ( viewport_start_x, viewport_start_y, viewport_size_x, viewport_size_y );
			Clear<true, true> ( );

			directional_light_shader_.UpdateShadowTextureMatrix ( ToUvMatrix ( ) * directional_light_matrix );

			opengl::Texture::SetActiveSlot ( 0 );
			directional_light_shader_.UpdateShadowTexture ( 0 );
			shadow_frame_buffer.BindDepthStencilTexture ( );
			opengl::Texture::SetActiveSlot ( 1 );
			directional_light_shader_.UpdateMaterialColourTexture ( 1 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::material_colour ) );
			opengl::Texture::SetActiveSlot ( 2 );
			directional_light_shader_.UpdateAmbientColourTexture ( 2 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::ambient_colour ) );
			opengl::Texture::SetActiveSlot ( 3 );
			directional_light_shader_.UpdateDiffuseTexture ( 3 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::diffuse ) );
			opengl::Texture::SetActiveSlot ( 4 );
			directional_light_shader_.UpdateSpecularTexture ( 4 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::specular ) );
			opengl::Texture::SetActiveSlot ( 5 );
			directional_light_shader_.UpdateSpecularFocusTexture ( 5 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::specular_focus ) );
			opengl::Texture::SetActiveSlot ( 6 );
			directional_light_shader_.UpdatePositionWorldspaceTexture ( 6 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::position_worldspace ) );
			opengl::Texture::SetActiveSlot ( 7 );
			directional_light_shader_.UpdatePositionCameraspaceTexture ( 7 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::position_cameraspace ) );
			opengl::Texture::SetActiveSlot ( 8 );
			directional_light_shader_.UpdateNormalCameraspaceTexture ( 8 );
			lighting_geometry_frame_buffer.BindColourTexture ( static_cast< GLuint >( StaticTexturedLightingMeshShader::Output::normal_cameraspace ) );
			return shader << Render ( directional_light_shader_, image );
		};
	}

	void SetCamera ( const Game::FirstPersonCamera& camera )
	{
		const Vector3 position = camera.GetPosition ( );
		const Vector3 grounded_position { position.X ( ), terrain.GetHeightMap ( ).Read ( ( position.X ( ) - -0.5f * 4000.f ) / 4000.f, ( position.Z ( ) - -0.5f * 4000.f) / 4000.f ) * 0.1f * 4000.f - 120.f, position.Z ( ) };

		look_position_ = grounded_position;
		look_direction_ = camera.GetView ( );
		look_up_ = camera.GetUp ( );
		view_ = view_.GetViewTransform ( grounded_position, camera.GetView ( ), camera.GetUp ( ) );
	}

	void UpdateSprite ( const float delta_time )
	{
		sprite_instance.Update ( delta_time );
	}

private:
	static constexpr GLuint shadow_texture_size_x = 1024 * 8;
	static constexpr GLuint shadow_texture_size_y = 1024 * 8;

	class ShadowFrameBufferSetter
	{
	public:
		void SetDepthStencil ( opengl::Texture& texture ) noexcept
		{
			texture.Bind ( );
			texture.SetDepthStencil ( shadow_texture_size_x, shadow_texture_size_y );
		}
		void SetDepth ( opengl::Texture& texture ) noexcept
		{
			texture.Bind ( );
			texture.SetDepth ( shadow_texture_size_x, shadow_texture_size_y );
		}
		void SetColour ( const GLuint index, opengl::Texture& texture ) noexcept
		{
			texture.Bind ( );
			texture.SetRGBAByte ( shadow_texture_size_x, shadow_texture_size_y );
		}
	};

	class LightingGeometryFrameBufferSetter
	{
	public:
		using ShaderOutput = StaticTexturedLightingMeshShader::Output;
		LightingGeometryFrameBufferSetter ( ) = default;
		LightingGeometryFrameBufferSetter ( const GLuint size_x, const GLuint size_y ) : size_x_ { size_x }, size_y_ { size_y }
		{

		}

		void SetDepthStencil ( opengl::Texture& texture ) noexcept
		{
			texture.Bind ( );
			texture.SetDepthStencil ( size_x_, size_y_ );
		}
		void SetDepth ( opengl::Texture& texture ) noexcept
		{
			texture.Bind ( );
			texture.SetDepth ( size_x_, size_y_ );
		}
		void SetColour ( const GLuint index, opengl::Texture& texture ) noexcept
		{
			switch ( static_cast< ShaderOutput >( index ) )
			{
				case ShaderOutput::position_worldspace:
				{
					texture.Bind ( );
					texture.SetRGBFloat ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::position_cameraspace:
				{
					texture.Bind ( );
					texture.SetRGBFloat ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::normal_cameraspace:
				{
					texture.Bind ( );
					texture.SetRGBFloat ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::ambient_colour:
				{
					texture.Bind ( );
					texture.SetRGBAByte ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::material_colour:
				{
					texture.Bind ( );
					texture.SetRGBAByte ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::diffuse:
				{
					texture.Bind ( );
					texture.SetRGBFloat ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::specular:
				{
					texture.Bind ( );
					texture.SetRGBFloat ( size_x_, size_y_ );
					break;
				}
				case ShaderOutput::specular_focus:
				{
					texture.Bind ( );
					texture.SetRFloat ( size_x_, size_y_ );
					break;
				}
			}
		}

	private:
		GLuint size_x_ { };
		GLuint size_y_ { };
	};

	opengl::VertexArray arr_;

	GLuint viewport_start_x;
	GLuint viewport_start_y;
	GLuint viewport_size_x;
	GLuint viewport_size_y;

	Vector3 direction_light_direction { 29, -7, -6 };
	Vector3 direction_light_colour { 1,1,1 };
	float direction_light_power = 1.f;

	Vector3 look_position_;
	Vector3 look_direction_;
	Vector3 look_up_;
	Matrix view_;
	Matrix perspective_;

	opengl::FrameBuffer<opengl::FRAME_BUFFER_MODE::DEPTH_STENCIL, 1> shadow_frame_buffer { ShadowFrameBufferSetter{} };
	opengl::FrameBuffer<opengl::FRAME_BUFFER_MODE::DEPTH_STENCIL, static_cast< std::size_t > ( StaticTexturedLightingMeshShader::Output::total )> lighting_geometry_frame_buffer;

	StaticTexturedMeshShader static_textured_mesh_shader_;
	StaticTexturedLightingMeshShader static_textured_lighting_mesh_shader_;
	StaticColouredMeshShader static_coloured_mesh_shader_;
	DirectionalLightShader directional_light_shader_;

	Image image;
	
	ObjMesh masterchief { "objs\\masterchief.obj" };
	ObjMesh raigon { "objs\\raigon.obj" };
	SkyPlane sky_plane { 60, 1.f, 5000.f, 1.f, 1.f };
	Terrain terrain { "textures\\height_map.tga", 1000, 0.1f };
	Sprite sprite { 7, 10, 15 };
	Sprite::Instance sprite_instance { sprite.GetInstance ( ) };
	TargaTexture sprite_texture { "textures\\Cyborg_Shooter\\Characters\\Heroes\\Hero_Kifellah.tga" };
	TargaTexture sky_texture { "textures\\sky.tga" };
	TargaTexture terrain_texture { "textures\\snow.tga" };
	TargaTexture masterchief_texture { "textures\\masterchief.tga" };
	TargaTexture raigon_texture { "textures\\raigon.tga" };
	TargaTexture snowflake_texture { "textures\\snowflake.tga" };
};