#include "Keyboard.h"

namespace opengl
{
	Key::Key ( const KEYS key, const KEY_STATE state, const std::bitset<4> modifiers, const int scancode ) noexcept : key_ ( key ), state_ ( state ), modifiers_ ( modifiers ), scancode_ ( scancode )
	{
	}

	KEYS Key::GetKey ( ) const noexcept
	{
		return key_;
	}

	KEY_STATE Key::GetState ( ) const noexcept
	{
		return state_;
	}

	int Key::GetScanCode ( ) const noexcept
	{
		return scancode_;
	}
}