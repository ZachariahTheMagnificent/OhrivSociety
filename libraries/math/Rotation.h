#pragma once
#include "Vector3.h"

namespace math
{
	template<class Float>
	class Rotation
	{
	public:
		using Vector3 = Vector3<Float>;

		Rotation ( ) = default;
		Rotation ( const Vector3 orgin_normal, const Vector3 destination_normal ) noexcept
		{
			Vector3 rotation_direction = destination_normal - orgin_normal;
			Vector3 half_destination = ( orgin_normal + rotation_direction / 2 ).Normalized();

			w_ = orgin_normal.Dot( half_destination );
			vector_ = orgin_normal.Cross( half_destination );
		}
		Rotation ( const Vector3 axis, const Float half_rotation) noexcept
		{
			const Float cosine = std::cos ( half_rotation );
			const Float sine = std::sin ( half_rotation );

			w_ = cosine;
			vector_ = axis * sine;
		}

		Rotation& operator*=( const Rotation rhs )
		{
			return *this = *this * rhs;
		}
		Rotation operator*( const Rotation rhs ) const
		{
			return Rotation { w_ * rhs.w_ - vector_.Dot ( rhs.vector_ ), vector_ * rhs.w_ + rhs.vector_ * w_ + vector_.Cross ( rhs.vector_ ) };
		}
		Vector3 operator*( const Vector3 vector ) const
		{
			// Actual formula
			//const Rotation point { 0.f, vector };
			//const Rotation rotation = *this;
			//return ( rotation * point * rotation.Inverse ( ) ).vector_;

			// More optimised version
			Vector3 cross_product = vector_.Cross ( vector );
			return vector + cross_product * ( 2 * w_ ) + vector_.Cross ( cross_product ) * 2;

		}

		constexpr Rotation Inverse ( ) const noexcept
		{
			return Rotation { w_, -vector_ };
		}

		constexpr Float X ( ) const noexcept
		{
			return vector_.X ( );
		}
		constexpr Float Y ( ) const noexcept
		{
			return vector_.Y ( );
		}
		constexpr Float Z ( ) const noexcept
		{
			return vector_.Z ( );
		}
		constexpr Float W ( ) const noexcept
		{
			return w_;
		}

		Float LengthSquared ( ) const noexcept
		{
			return vector_.LengthSquared ( ) + w_ * w_;
		}
		Float Length ( ) const noexcept
		{
			return std::sqrt ( LengthSquared ( ) );
		}

		Rotation Normalized ( ) const noexcept
		{
			const Float length = Length ( );

			return Rotation { w_ / length, vector_ / length };
		}

	private:
		constexpr Rotation ( const Float w, const Vector3 vector ) noexcept : w_ { w }, vector_ { vector }
		{

		}

		Float w_ { 1.f };
		Vector3 vector_ { };
	};
}