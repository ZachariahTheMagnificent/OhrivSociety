#pragma once

namespace data_structure
{
	template<typename T, typename U>
	size_t OffsetOf ( const U T::*member )
	{
		return ( char* )&( ( T* )nullptr->*member ) - ( char* )nullptr;
	}
}