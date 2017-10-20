#include "Connection.h"

namespace winsock
{
	Connection::Connection ( const SOCKET handle, const Address& local_address, const Address& remote_address ) : Socket { handle }, local_address_ { local_address }, remote_address_ { remote_address }
	{
		StartCheckForReceivedBytesTask ( std::vector<char> ( ) );
	}

	Connection::Connection ( Address address, const Config& config ) : Socket { config }, remote_address_ { address }
	{
		if ( connect ( GetHandle ( ), GetAddressPointer( address ), GetAddressSize( address ) ) == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}

		//local_address_ = lol I dunno

		StartCheckForReceivedBytesTask ( std::vector<char> ( ) );
	}

	const Address& Connection::GetLocalAddress ( ) const noexcept
	{
		return local_address_;
	}

	const Address& Connection::GetRemoteAddress ( ) const noexcept
	{
		return remote_address_;
	}

	void Connection::Send ( std::string message )
	{
		while ( true )
		{
			const int flags = 0;
			const int message_size = message.size ( ) + 1;
			const int sent_bytes = send ( GetHandle ( ), message.c_str ( ), message_size * sizeof ( char ), flags );

			if ( sent_bytes == SOCKET_ERROR )
			{
				throw Exception { WSAGetLastError ( ) };
			}
			else if ( sent_bytes == message_size )
			{
				break;
			}

			message = message.substr ( sent_bytes );
		}
	}

	void Connection::Send ( std::vector<char> bytes )
	{
		while ( true )
		{
			const int flags = 0;
			const int message_size = bytes.size ( );
			const int sent_bytes = send ( GetHandle ( ), &bytes.front ( ), message_size * sizeof ( char ), flags );

			if ( sent_bytes == SOCKET_ERROR )
			{
				throw Exception { WSAGetLastError ( ) };
			}
			else if ( sent_bytes == message_size )
			{
				break;
			}

			bytes.erase ( bytes.begin ( ), bytes.begin ( ) + sent_bytes );
		}
	}

	void Connection::StartCheckForReceivedBytesTask ( std::vector<char> buffer )
	{
		SOCKET current_handle = GetHandle ( );

		task_is_done_ = std::async ( std::launch::async, [ current_handle ] ( std::vector<char> bytes )
		{
			const int flags = 0;
			bytes.resize ( MAX_RECV_BYTES / sizeof ( bytes.front ( ) ) );
			const int received_bytes = recv ( current_handle, &bytes.front ( ), MAX_RECV_BYTES, flags );

			if ( received_bytes == SOCKET_ERROR )
			{
				throw Exception { WSAGetLastError ( ) };
			}
			else if ( received_bytes == 0 )
			{
				throw Exception { Exception::Type::DISCON };
			}

			bytes.resize ( received_bytes );

			return bytes;
		}, std::move ( buffer ) );
	}
}