#include "Socket.h"

namespace winsock
{
	Socket::Socket ( const Config& config ) : handle_ { CreateHandle ( config ) }
	{
	}

	Socket::Socket ( Address address, const Config& config ) : Socket { config }
	{
		if ( bind ( handle_.get ( ), GetAddressPointer ( address ), GetAddressSize ( address ) ) == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}
	}

	bool Socket::Initialized ( ) const noexcept
	{
		return bool { handle_ };
	}

	Socket::Socket ( const SOCKET handle ) noexcept : handle_ { handle }
	{
	}

	SOCKET Socket::GetHandle ( ) const noexcept
	{
		return handle_.get ( );
	}

	SOCKET Socket::CreateHandle ( const Config& config )
	{
		SOCKET handle = socket ( config.GetFamily ( ), config.GetSocktype ( ), config.GetProtocol ( ) );
		if ( handle == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}

		return handle;
	}

	int Socket::Config::GetFamily ( ) const noexcept
	{
		return family_;
	}
	int Socket::Config::GetSocktype ( ) const noexcept
	{
		return socktype_;
	}
	int Socket::Config::GetProtocol ( ) const noexcept
	{
		return protocol_;
	}

	Socket::Config::Config ( const int family, const int socktype, const int protocol ) noexcept : family_ { family }, socktype_ { socktype }, protocol_ { protocol }
	{
	}

	Socket::Config Socket::Config::Creator::CreateConfig ( const int family, const int socktype, const int protocol ) noexcept
	{
		return Config { family, socktype, protocol };
	}

	void Socket::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		closesocket ( pointer );
	}
}