#include "Book.h"
#include <memory>

namespace winsock
{
	class AddrInfo
	{
	public:
		class Iterator
		{
		public:
			Iterator ( ) = default;

			Iterator ( const addrinfo* info ) noexcept : current_info_ { info }
			{
			}

			Iterator& operator++( ) noexcept
			{
				current_info_ = current_info_->ai_next;
				return *this;
			}

			bool operator!=( const Iterator& iterator ) const noexcept
			{
				return current_info_ != iterator.current_info_;
			}
			const addrinfo& operator*( ) const noexcept
			{
				return *current_info_;
			}

		private:
			const addrinfo* current_info_ { nullptr };
		};

		AddrInfo ( ) = default;
		AddrInfo ( const std::string& name, const std::string& port, addrinfo hints ) : handle_ { CreateHandle ( name, port, hints ) }
		{
		}
		AddrInfo ( const std::string& port, const addrinfo& hints ) : AddrInfo { "", port, hints }
		{
		}

		AddrInfo ( const AddrInfo& addr_info ) = delete;
		AddrInfo& operator=( const AddrInfo& addr_info ) = delete;

		AddrInfo ( AddrInfo&& addr_info ) = default;
		AddrInfo& operator=( AddrInfo&& addr_info ) = default;

		bool Initialized ( ) const noexcept
		{
			return bool { handle_ };
		}

		Iterator begin ( ) const noexcept
		{
			return Iterator { handle_.get ( ) };
		}
		Iterator end ( ) const noexcept
		{
			return Iterator { nullptr };
		}

	private:
		class Deleter
		{
		public:
			void operator() ( addrinfo*const info ) const noexcept
			{
				freeaddrinfo ( info );
			}
		};
		using Handle = std::unique_ptr<addrinfo, Deleter>;

		static addrinfo* CreateHandle ( const std::string& name, const std::string& port, addrinfo hints )
		{
			addrinfo* info;
			const int error = getaddrinfo ( name.c_str ( ), port.c_str ( ), &hints, &info );
			if ( error != NO_ERROR )
			{
				throw Exception { error };
			}
			return info;
		}

		Handle handle_ { nullptr };
	};

	SocketInfo::SocketInfo ( const Address& address, const Socket::Config& config ) noexcept : address { address }, required_socket_config { config }
	{
	}

	NamedSocketInfo::NamedSocketInfo ( const std::string& name, const SocketInfo& info ) noexcept : SocketInfo { info }, name ( name )
	{
	}

	Book::NamedSocketInfoList Book::LookUp ( const std::string& hostname, const std::string& port, const Socket::Family family, const Socket::Protocol protocol, const bool give_cannon_name ) const
	{
		addrinfo hints { };
		switch ( family )
		{
			case Socket::Family::IPV4:
				hints.ai_family = AF_INET;
				break;
			case Socket::Family::IPV6:
				hints.ai_family = AF_INET6;
				break;
			case Socket::Family::UNSPECIFIED:
				hints.ai_family = AF_UNSPEC;
				break;
		}
		switch ( protocol )
		{
			case Socket::Protocol::TCP:
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO::IPPROTO_TCP;
				break;
			case Socket::Protocol::UDP:
				hints.ai_socktype = SOCK_DGRAM;
				hints.ai_protocol = IPPROTO::IPPROTO_UDP;
				break;
		}

		if ( give_cannon_name )
		{
			hints.ai_flags = AI_CANONNAME;
		}
		else
		{
			hints.ai_flags = AI_FQDN;
		}

		const AddrInfo addr_info { hostname, port, hints };

		NamedSocketInfoList buffer;

		for ( const addrinfo info : addr_info )
		{
			const Address address = CreateAddress ( info.ai_addr );
			const Socket::Config config = CreateConfig ( info.ai_family, info.ai_socktype, info.ai_protocol );
			const SocketInfo addr_info { address, config };
			buffer.emplace_back ( info.ai_canonname, addr_info );
		}

		return buffer;
	}

	Book::SocketInfoList Book::LookUp ( const std::string& port, const Socket::Family family, const Socket::Protocol protocol ) const
	{
		addrinfo hints { };
		switch ( family )
		{
			case Socket::Family::IPV4:
				hints.ai_family = AF_INET;
				break;
			case Socket::Family::IPV6:
				hints.ai_family = AF_INET6;
				break;
			case Socket::Family::UNSPECIFIED:
				hints.ai_family = AF_UNSPEC;
				break;
		}
		switch ( protocol )
		{
			case Socket::Protocol::TCP:
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO::IPPROTO_TCP;
				break;
			case Socket::Protocol::UDP:
				hints.ai_socktype = SOCK_DGRAM;
				hints.ai_protocol = IPPROTO::IPPROTO_UDP;
				break;
		}
		hints.ai_flags = AI_PASSIVE;

		const AddrInfo addr_info ( port, hints );

		SocketInfoList buffer;

		for ( const addrinfo info : addr_info )
		{
			const Address address = CreateAddress( info.ai_addr );
			const Socket::Config config = CreateConfig ( info.ai_family, info.ai_socktype, info.ai_protocol );
			buffer.emplace_back ( address, config );
		}

		return buffer;
	}
}