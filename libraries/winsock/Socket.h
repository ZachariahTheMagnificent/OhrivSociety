#pragma once
#include <memory>
#include "Address.h"
#include "Exception.h"

namespace winsock
{
	class Socket : protected Address::User
	{
	public:
		enum class Family
		{
			IPV4,
			IPV6,
			UNSPECIFIED
		};

		enum class Protocol
		{
			TCP,
			UDP
		};

		class Config
		{
		public:
			class Creator
			{
			protected:
				static Config CreateConfig ( const int family, const int socktype, const int protocol ) noexcept;
			};

			int GetFamily ( ) const noexcept;
			int GetSocktype ( ) const noexcept;
			int GetProtocol ( ) const noexcept;

		private:
			explicit Config ( const int family, const int socktype, const int protocol ) noexcept;

			int family_ { };
			int socktype_ { };
			int protocol_ { };
		};

		static constexpr std::size_t MAX_SENT_BYTES = SO_SNDBUF;
		static constexpr std::size_t MAX_RECV_BYTES = SO_RCVBUF;

		Socket ( ) = default;
		explicit Socket ( const Config& config );
		explicit Socket ( Address address, const Config& config );

		Socket ( const Socket& socket ) = delete;
		Socket& operator=( const Socket& socket ) = delete;

		Socket ( Socket&& socket ) = default;
		Socket& operator=( Socket&& socket ) = default;

		bool Initialized ( ) const noexcept;

	protected:
		Socket ( const SOCKET handle ) noexcept;

		SOCKET GetHandle ( ) const noexcept;

	private:
		class Deleter
		{
		public:
			using pointer = SOCKET;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<SOCKET, Deleter>;

		static SOCKET CreateHandle ( const Config& config );

		Handle handle_ { };
	};
}