#pragma once
#include <utility>
#include <string>
#include <ws2tcpip.h>
#include <winsock2.h>

namespace winsock
{
	class Address
	{
	public:
		class Creator
		{
		protected:
			static Address CreateAddress ( const sockaddr*const address ) noexcept;
			static Address CreateAddress ( const sockaddr_storage address ) noexcept;
		};

		class User : protected Creator
		{
		protected:
			static sockaddr* GetAddressPointer ( Address& address ) noexcept;
			static std::size_t GetAddressSize ( const Address& address ) noexcept;
		};

		Address ( ) = default;

	private:
		Address ( const sockaddr_storage address ) noexcept;

		sockaddr_storage address_ { };
	};
}