#pragma once
#include <vector>
#include "Socket.h"

namespace winsock
{
	struct SocketInfo
	{
		SocketInfo ( ) = default;
		explicit SocketInfo ( const Address& address, const Socket::Config& config ) noexcept;

		Address address;
		Socket::Config required_socket_config;
	};

	struct NamedSocketInfo : public SocketInfo
	{
		NamedSocketInfo ( ) = default;
		explicit NamedSocketInfo ( const std::string& name, const SocketInfo& info ) noexcept;

		std::string name;
	};

	class Book : private Address::Creator, private Socket::Config::Creator
	{
	public:
		using SocketInfoList = std::vector<SocketInfo>;
		using NamedSocketInfoList = std::vector<NamedSocketInfo>;

		Book ( ) = default;

		NamedSocketInfoList LookUp ( const std::string& hostname, const std::string& port, const Socket::Family family, const Socket::Protocol protocol, const bool give_cannon_name ) const;
		SocketInfoList LookUp ( const std::string& port, const Socket::Family family, const Socket::Protocol protocol ) const;
	};
}