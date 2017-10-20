#include "Address.h"

namespace winsock
{
	Address::Address ( const sockaddr_storage address ) noexcept : address_ ( address )
	{
	}

	Address Address::Creator::CreateAddress ( const sockaddr*const address ) noexcept
	{
		return Address { *reinterpret_cast< const sockaddr_storage*const >( address ) };
	}

	Address Address::Creator::CreateAddress ( const sockaddr_storage address ) noexcept
	{
		return Address { address };
	}

	sockaddr* Address::User::GetAddressPointer ( Address& address ) noexcept
	{
		return reinterpret_cast< sockaddr* >( &address.address_ );
	}

	std::size_t Address::User::GetAddressSize ( const Address& address ) noexcept
	{
		return sizeof ( address.address_ );
	}
}