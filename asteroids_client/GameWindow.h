#pragma once
#include "opengl\Window.h"
#include "GameRenderer.h"
#include "Game.h"

class GameWindow : public opengl::Window<GameWindow, GameRenderer>
{
	friend Window;

public:
	using Vector3 = Game::Vector3;

	GameWindow ( Game& game ) : Window { "Graphics", 1920, 1080, false }, game_ { game }
	{
		UseLockedMouse ( );
		auto mouse_pos = GetMousePosition ( );
		prev_xpos_ = mouse_pos.x;
		prev_ypos_ = mouse_pos.y;
		prev_time_point = std::chrono::steady_clock::now ( );
	}

	GameWindow ( const GameWindow& ) = delete;
	GameWindow& operator=( const GameWindow& ) = delete;

	void Update ( )
	{
		const auto current_time_point = std::chrono::steady_clock::now ( );
		const auto duration = current_time_point - prev_time_point;
		const float delta_time = std::chrono::duration_cast< std::chrono::duration<float> >( duration ).count ( );
		prev_time_point = current_time_point;
		MakeContextCurrent ( );
		UseLockedMouse ( );

		game_.Update ( delta_time );

		renderer_.Render ( game_ );

		SwapBuffers ( );
	}

private:
	void OnWindowResized ( const int width, const int height )
	{

	}
	void OnFrameBufferResized ( const int width, const int height )
	{
		renderer_.SetViewProperties ( 0, 0, width, height );
	}
	void OnCharacterEntered ( const unsigned character )
	{

	}
	void OnKeyEntered ( const opengl::Key key )
	{
		if ( key.GetKey ( ) == opengl::KEYS::ESCAPE )
		{
			SetToClose ( );
			return;
		}

		if ( key.GetKey ( ) == opengl::KEYS::W )
		{
			if ( key.GetState ( ) == opengl::KEY_STATE::PRESS )
			{
				Game::InputManager::OnMoveUp<true> ( game_ );
			}
			else if ( key.GetState ( ) == opengl::KEY_STATE::RELEASE )
			{
				Game::InputManager::OnMoveUp<false> ( game_ );
			}
		}
		else if ( key.GetKey ( ) == opengl::KEYS::S )
		{
			if ( key.GetState ( ) == opengl::KEY_STATE::PRESS )
			{
				Game::InputManager::OnMoveDown<true> ( game_ );
			}
			else if ( key.GetState ( ) == opengl::KEY_STATE::RELEASE )
			{
				Game::InputManager::OnMoveDown<false> ( game_ );
			}
		}
		else if ( key.GetKey ( ) == opengl::KEYS::A )
		{
			if ( key.GetState ( ) == opengl::KEY_STATE::PRESS )
			{
				Game::InputManager::OnMoveLeft<true> ( game_ );
			}
			else if ( key.GetState ( ) == opengl::KEY_STATE::RELEASE )
			{
				Game::InputManager::OnMoveLeft<false> ( game_ );
			}
		}
		else if ( key.GetKey ( ) == opengl::KEYS::D )
		{
			if ( key.GetState ( ) == opengl::KEY_STATE::PRESS )
			{
				Game::InputManager::OnMoveRight<true> ( game_ );
			}
			else if ( key.GetState ( ) == opengl::KEY_STATE::RELEASE )
			{
				Game::InputManager::OnMoveRight<false> ( game_ );
			}
		}
	}
	void OnFileDropped ( const std::string& file_path )
	{

	}
	void OnMouseEnter ( )
	{

	}
	void OnMouseExit ( )
	{

	}
	void OnMouseMove ( const double xpos, const double ypos )
	{
		const float delta_x = static_cast< float >( prev_xpos_ - xpos );
		const float delta_y = static_cast< float >( prev_ypos_ - ypos );

		prev_xpos_ = xpos;
		prev_ypos_ = ypos;
		Game::InputManager::OnRotateCamera ( game_, delta_x * 0.001f, delta_y * 0.001f );
	}
	void OnScroll ( const double xoffset, const double yoffset )
	{

	}

	double prev_xpos_ { };
	double prev_ypos_ { };
	std::chrono::steady_clock::time_point prev_time_point { };
	Game& game_;
};