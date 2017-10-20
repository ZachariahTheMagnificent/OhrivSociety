#pragma once
#include <string>
#include <memory>
#include <ws2tcpip.h>
#include <winsock2.h>
#include "Exception.h"
#include "Book.h"
#include "Connection.h"
#include "Server.h"

namespace winsock
{
	class Application
	{
	public:
		Application ( );

		Application ( const Application& ) = delete;
		Application& operator=( const Application& ) = delete;

		Application ( Application&& app ) = default;
		Application& operator=( Application&& app ) = default;

		bool Initialized ( ) const noexcept;

		std::string GetHostName ( ) const;

	private:
		class ComparableWSAData : public WSAData
		{
		public:
			ComparableWSAData ( ) noexcept;
			ComparableWSAData ( const WSAData& data ) noexcept;
			ComparableWSAData ( const ComparableWSAData& data ) noexcept;
			ComparableWSAData ( ComparableWSAData&& data ) noexcept;

			ComparableWSAData& operator=( const ComparableWSAData& data ) noexcept;
			ComparableWSAData& operator=( ComparableWSAData&& data ) noexcept;

			bool operator==( const WSAData& rhs ) const noexcept;
			bool operator!=( const WSAData& rhs ) const noexcept;
		};

		class Deleter
		{
		public:
			using pointer = ComparableWSAData;

			void operator()( const pointer& pointer ) const noexcept;
		};
		using Handle = std::unique_ptr<ComparableWSAData, Deleter>;

		static ComparableWSAData InitWinsock ( );

		Handle handle_;
	};
}