#pragma once
#include <exception>
#include <cmath>

namespace math
{
	/******************************************************************************/
	//Exceptions!
	/******************************************************************************/

	/******************************************************************************/
	/*!
	\brief
	Exception for divide by zero.
	*/
	/******************************************************************************/
	class DivideByZero : public std::exception
	{
	public:
		/******************************************************************************/
		/*!
		\brief
		Returns the error message.

		*/
		/******************************************************************************/
		const char* what ( ) const noexcept override;
	};
	class MustBeUnit : public std::exception
	{
	public:
		const char* what ( ) const noexcept override;
	};

	/******************************************************************************/
	//Constants!
	/******************************************************************************/

	template<class Type>
	constexpr Type Pi ( ) noexcept
	{
		return static_cast< Type >( 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233L );
	}
	template<class Type>
	constexpr Type Tau ( ) noexcept
	{
		return static_cast< Type >( 6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341359642961730265646132941876892191011644634507188162569622349005682054038770422111192892458979098607639288576219513318668922569512964675735663305424038182L );
	}
	template<class Type>
	constexpr Type FullDegree ( ) noexcept
	{
		return static_cast< Type >( 360 );
	}
	template<class Type>
	constexpr Type Epsilon ( ) noexcept
	{
		return static_cast< Type >( 0.0001L );
	}

	/******************************************************************************/
	//Functions!
	/******************************************************************************/

	template<class Type>
	constexpr Type Abs ( const Type value ) noexcept
	{
		return value < 0 ? -value : value;
	}

	template<class Type>
	constexpr Type DegreeToRadian ( const Type value ) noexcept
	{
		return value * Tau<Type> ( ) / FullDegree<Type> ( );
	}
	template<class Type>
	constexpr Type RadianToDegree ( const Type value ) noexcept
	{
		return value * FullDegree<Type> ( ) / Tau<Type> ( );
	}

	template<class Type>
	constexpr bool AlmostEquals ( const Type a, const Type b ) noexcept
	{
		return Abs ( a - b ) <= Epsilon<Type> ( );
	}
	template<class Type>
	constexpr Type Reciprocal ( const Type value ) noexcept
	{
		return static_cast< Type >( 1.0L ) / value;
	}

	template<class Type>
	constexpr Type Wrap ( const Type value, const Type start, const Type end ) noexcept
	{
		if ( value < start )
		{
			return end;
		}
		else if ( value > end )
		{
			return start;
		}
		else
		{
			return value;
		}
	}
	template<class Type>
	constexpr Type Clamp ( const Type value, const Type start, const Type end ) noexcept
	{
		if ( value < start )
		{
			return start;
		}
		else if ( value > end )
		{
			return end;
		}
		else
		{
			return value;
		}
	}
}