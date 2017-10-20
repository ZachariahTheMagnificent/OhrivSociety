#pragma once
#include "Connection.h"

namespace winsock
{
	class Server : public Socket
	{
	public:
		Server ( ) = default;
		explicit Server ( Address address, const Config& config );

		Server ( const Server& server ) = delete;
		Server& operator=( const Server& server ) = delete;

		Server ( Server&& server ) = default;
		Server& operator=( Server&& server ) = default;

		const Address& GetAddress ( ) const noexcept;

		template<class OnConnectionCreated>
		void CheckForConnections ( OnConnectionCreated&& on_connection_created )
		{
			std::chrono::nanoseconds duration { 0 };
			if ( connection_received_.wait_for ( duration ) == std::future_status::ready )
			{
				Connection new_connection = connection_received_.get ( );
				on_connection_created ( std::move ( new_connection ) );
				CreateListenerTask ( );
			}
		}

	private:
		void CreateListenerTask ( );

		std::future<Connection> connection_received_;

		Address address_;
	};
}