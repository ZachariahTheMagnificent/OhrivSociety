#pragma once
#include "Camera.h"
#include <math\Rotation.h>

template<class Float>
class FirstPersonCamera : public Camera<Float>
{
public:
	static constexpr Vector3 default_up = Vector3 { 0, 1, 0 };

	FirstPersonCamera ( ) noexcept : Camera { Vector3 { }, Vector3 { 0, 0, -1 }, Vector3 { 0, 1, 0 } }
	{

	}

	void Move ( const Vector3 delta_positon ) noexcept
	{
		position_ += delta_positon;
	}

	void Rotate ( const float yaw, const float pitch ) noexcept
	{
		const auto view = view_;
		const auto up = up_;
		const auto right = view.Cross ( up ).Normalized ( );
		const auto rotation = Rotation { default_up, yaw } * Rotation { right, pitch };

		const auto new_view = rotation * view;
		const auto new_right = new_view.Cross ( default_up );
		const auto new_up = new_right.Cross ( new_view );

		view_ = new_view.Normalized ( );
		up_ = new_up.Normalized ( );
	}
};