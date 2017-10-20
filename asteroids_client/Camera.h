#pragma once
#include <math\Vector3.h>
#include <math\Matrix4x4.h>

template<class Float>
class Camera
{
public:
	using Vector3 = math::Vector3<Float>;
	using Normal = typename Vector3::Normal;
	using Matrix = math::Matrix<Float>;
	using Rotation = math::Rotation<Float>;

	constexpr Vector3 GetPosition ( ) const noexcept
	{
		return position_;
	}
	constexpr Normal GetView ( ) const noexcept
	{
		return view_;
	}
	constexpr Normal GetRight ( ) const noexcept
	{
		return view_.Cross ( up_ ).Normalized ( );
	}
	constexpr Normal GetLeft ( ) const noexcept
	{
		return up_.Cross ( view_ ).Normalized ( );
	}
	constexpr Normal GetUp ( ) const noexcept
	{
		return up_;
	}

protected:
	explicit constexpr Camera ( const Vector3 position, const Vector3 view, const Vector3 up ) noexcept : position_ { position }, view_ { view }, up_ { up }
	{

	}

	Vector3 position_ { };
	Normal view_ { };
	Normal up_ { };
};