#include "PathFinder.h"

#pragma comment(lib, "math.lib")

namespace ai
{
	bool PathFinder::Connected ( const Vector3 position1, const Vector3 position2 )
	{
		bool collide = false;

		const Vector3 from_1_to_2 = position2 - position1;

		for ( const Line line : line_boundaries_ )
		{
			if ( line.CrossesWith ( Line { position1, from_1_to_2 } ) )
			{
				collide = true;
			}
		}
		return !collide;
	}
}