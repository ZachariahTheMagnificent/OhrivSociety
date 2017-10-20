#pragma once
#include <future>
#include <memory>
#include "Socket.h"
#include "Exception.h"
#include "Address.h"

namespace winsock
{
	class Connection : public Socket
	{
	public:
		Connection ( ) = default;
		explicit Connection ( const SOCKET handle, const Address& local_address, const Address& remote_address );
		explicit Connection ( Address address, const Config& config );
		
		Connection ( const Connection& connection ) = delete;
		Connection& operator=( const Connection& connection ) = delete;

		Connection ( Connection&& connection ) = default;
		Connection& operator=( Connection&& connection ) = default;

		const Address& GetLocalAddress ( ) const noexcept;
		const Address& GetRemoteAddress ( ) const noexcept;

		void Send ( std::string message );
		void Send ( std::vector<char> bytes );

		template<class OnReceivedBytes>
		void CheckForBytes ( OnReceivedBytes&& on_received_bytes )
		{
			std::chrono::nanoseconds duration { 0 };
			if ( task_is_done_.valid ( ) )
			{
				if ( task_is_done_.wait_for ( duration ) == std::future_status::ready )
				{
					std::vector<char> bytes = task_is_done_.get ( );
					on_received_bytes ( bytes );
					StartCheckForReceivedBytesTask ( std::move ( bytes ) );
				}
			}
			else
			{
				StartCheckForReceivedBytesTask ( std::vector<char> ( ) );
			}
		}

	private:
		void StartCheckForReceivedBytesTask ( std::vector<char> buffer );

		std::future<std::vector<char>> task_is_done_;

		Address local_address_;
		Address remote_address_;
	};
}