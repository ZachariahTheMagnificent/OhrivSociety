/******************************************************************************/
/*!
\file	Vector3.h
\author	Muhammad Shafik Bin Mazlinan
\par	email: cyboryxmen\@yahoo.com
\brief
Contains the declaration of the Vector3 class.

*/
/******************************************************************************/
#pragma once
#include "Basic.h"
#include <array>

namespace math
{
	/******************************************************************************/
	/*!
	\brief
	Defines a 3 dimentional vector with three variables representing each axis value.


	\exception None
	\return the angle in radians
	*/
	/******************************************************************************/
	template<class Float>
	class Vector3
	{
		Float x_ { };
		Float y_ { };
		Float z_ { };

	public:
		class Normal : public Vector3
		{
		public:
			Normal ( ) = default;
			explicit Normal ( const Vector3 vector ) : Normal { Normalize ( vector ) }
			{

			}

			Normal operator-( ) const noexcept
			{
				return Normal { -x_, -y_, -z_ };
			}
			Normal Normalized ( ) const noexcept
			{
				return *this;
			}

			constexpr Float Length ( ) const noexcept
			{
				return length;
			}
			constexpr Float LengthSquared ( ) const noexcept
			{
				return length * length;
			}
			constexpr bool IsZero ( ) const noexcept
			{
				return length == 0;
			}
			constexpr bool IsUnit ( ) const noexcept
			{
				return length == 1;
			}

		private:
			static constexpr Float length = 1;

			explicit Normal ( const Float x, const Float y, const Float z ) : Vector3 { x, y, z }
			{

			}

			static Normal Normalize ( const Vector3 vector ) noexcept
			{
				const Float length = vector.Length ( );

				return Normal { vector.x_ / length, vector.y_ / length, vector.z_ / length };
			}
		};

		Vector3 ( ) = default;

		constexpr explicit Vector3 ( const Float x, const Float y, const Float z ) noexcept : x_ { x }, y_ { y }, z_ { z }
		{
		}

		explicit Vector3 ( const std::array<float, 3>& array ) noexcept : x_ { array [ 0 ] }, y_ { array [ 1 ] }, z_ { array [ 2 ] }
		{
		}

		Vector3& operator+=( const Vector3 vector ) noexcept
		{
			x_ += vector.x_;
			y_ += vector.y_;
			z_ += vector.z_;
			return *this;
		}
		constexpr Vector3 operator+( const Vector3 vector ) const noexcept
		{
			return Vector3 { x_ + vector.x_, y_ + vector.y_, z_ + vector.z_ };
		}

		Vector3& operator-=( const Vector3 vector ) noexcept
		{
			x_ -= vector.x_;
			y_ -= vector.y_;
			z_ -= vector.z_;
			return *this;
		}
		constexpr Vector3 operator-( const Vector3 vector ) const noexcept
		{
			return Vector3 { x_ - vector.x_, y_ - vector.y_, z_ - vector.z_ };
		}

		constexpr Vector3 operator-( ) const noexcept
		{
			return Vector3 { -x_, -y_, -z_ };
		}

		Vector3& operator*=( const Float scalar ) noexcept
		{
			x_ *= scalar;
			y_ *= scalar;
			z_ *= scalar;
			return *this;
		}
		constexpr Vector3 operator*( const Float scalar ) const noexcept
		{
			return Vector3 { x_ * scalar, y_ * scalar, z_ * scalar };
		}


		Vector3& operator/=( const Float scalar ) noexcept
		{
			x_ /= scalar;
			y_ /= scalar;
			z_ /= scalar;
			return *this;
		}
		constexpr Vector3 operator/( const Float scalar ) const noexcept
		{
			return Vector3 { x_ / scalar, y_ / scalar, z_ / scalar };
		}

		constexpr bool operator==( const Vector3 vector ) const noexcept
		{
			return AlmostEquals ( x_, vector.x_ ) && AlmostEquals ( y_, vector.y_ ) && AlmostEquals ( z_, vector.z_ );
		}
		constexpr bool operator!=( const Vector3 vector ) const noexcept
		{
			return !AlmostEquals ( x_, vector.x_ ) || !AlmostEquals ( y_, vector.y_ ) || !AlmostEquals ( z_, vector.z_ );
		}

		Float Length ( ) const noexcept
		{
			return std::sqrt ( LengthSquared ( ) );
		}
		Float LengthSquared ( ) const noexcept
		{
			return x_ * x_ + y_ * y_ + z_ * z_;
		}
		Normal Normalized ( ) const noexcept
		{
			return Normal { *this };
		}
		constexpr bool IsZero ( ) const noexcept
		{
			return AlmostEquals ( x_, Float { } ) && AlmostEquals ( y_, Float { } ) && AlmostEquals ( z_, Float { } );
		}
		constexpr bool IsUnit ( ) const noexcept
		{
			return AlmostEquals ( LengthSquared ( ), Float { 1.L } );
		}

		constexpr Float Dot ( const Vector3 vector ) const noexcept
		{
			return x_ * vector.x_ + y_ * vector.y_ + z_ * vector.z_;
		}
		constexpr Vector3 Cross ( const Vector3 vector ) const noexcept
		{
			return Vector3 { y_ * vector.z_ - z_ * vector.y_, z_ * vector.x_ - x_ * vector.z_, x_ * vector.y_ - y_ * vector.x_ };
		}

		constexpr Float X ( ) const noexcept
		{
			return x_;
		}
		constexpr Float Y ( ) const noexcept
		{
			return y_;
		}
		constexpr Float Z ( ) const noexcept
		{
			return z_;
		}

		std::array<Float, 3> array ( ) const noexcept
		{
			return { x_, y_, z_ };
		}
	};

	template<class Float>
	Vector3<Float> operator*( const Float scalar, const Vector3<Float> vector )
	{
		return vector * scalar;
	}
	template<class Float>
	Vector3<Float> operator/( const Float scalar, const Vector3<Float> vector )
	{
		return vector / scalar;
	}
}