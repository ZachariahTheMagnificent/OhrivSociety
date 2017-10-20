#include "Server.h"

namespace winsock
{
	Server::Server ( Address address, const Config& config ) : Socket { address, config }, address_ { address }
	{
		SOCKET handle = GetHandle ( );
		if ( listen ( GetHandle ( ), SOMAXCONN ) == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}

		if ( shutdown ( handle, SD_BOTH ) == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}

		CreateListenerTask ( );
	}

	const Address& Server::GetAddress ( ) const noexcept
	{
		return address_;
	}

	void Server::CreateListenerTask ( )
	{
		const SOCKET current_handle = GetHandle ( );
		const Address local_address = address_;

		connection_received_ = std::async ( std::launch::async, [ current_handle, local_address ] ( )
		{
			sockaddr_storage received_connection_address;
			int address_size = sizeof ( received_connection_address );

			SOCKET result = accept ( current_handle, reinterpret_cast< sockaddr* >( &received_connection_address ), &address_size );
			if ( result == SOCKET_ERROR )
			{
				const int error = WSAGetLastError ( );
				throw Exception { error };
			}

			return Connection { result, local_address, CreateAddress( received_connection_address ) };
		}
		);
	}
}