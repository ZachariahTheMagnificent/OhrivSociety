#pragma once
#include "Vector3.h"

namespace math
{
	template<class Float>
	class Line final
	{
	public:
		static_assert( std::is_same<Float, float>::value ||
					   std::is_same<Float, double>::value ||
					   std::is_same<Float, long double>::value, "Class Template Line from namespace math only accepts floating point types!" );

		Line ( ) = default;
		Line ( const Vector3<Float>& orgin, const Vector3<Float>& vector );

		const Vector3<Float>& Orgin ( ) const;
		const Vector3<Float>& Vector ( ) const;

		bool CrossesWith ( const Line& line ) const;

	private:
		Vector3<Float> orgin_;
		Vector3<Float> vector_;
	};
}