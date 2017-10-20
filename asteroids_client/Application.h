#pragma once
#include <opengl\Application.h>
#include "GameWindow.h"

class Application : public opengl::Application
{
public:
	void Run ( )
	{
		while ( !window_.ShouldClose ( ) )
		{
			PollEvents ( );
			window_.Update ( );
		}
	}

private:
	GameWindow window_ { game_ };
	Game game_;
};