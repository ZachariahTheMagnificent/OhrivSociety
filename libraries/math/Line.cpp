#include "Line.h"

namespace math
{
	template<class Float>
	Line<Float>::Line ( const Vector3<Float>& orgin, const Vector3<Float>& vector ) : orgin_ ( orgin ), vector_ ( vector )
	{
	}

	template<class Float>
	const Vector3<Float>& Line<Float>::Orgin ( ) const
	{
		return orgin_;
	}

	template<class Float>
	const Vector3<Float>& Line<Float>::Vector ( ) const
	{
		return vector_;
	}

	template<class Float>
	bool Line<Float>::CrossesWith ( const Line& line ) const
	{
		//http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect

		//Given that the intersection is equal to orgin1 + vector1 * t = orgin2 + vector2 * u:
		const Float t = ( line.orgin_ - orgin_ ).Cross ( line.vector_ ).Z ( ) / vector_.Cross ( line.vector_ ).Z ( );
		const Float u = ( orgin_ - line.orgin_ ).Cross ( vector_ ).Z ( ) / line.vector_.Cross ( vector_ ).Z ( );

		return t >= 0 && t <= 1 && u >= 0 && u <= 1;
	}

	template class Line<float>;
	template class Line<double>;
	template class Line<long double>;
}