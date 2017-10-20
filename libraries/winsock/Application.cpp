#include "Application.h"

#pragma comment(lib, "data_structure.lib")
#pragma comment(lib, "Ws2_32.lib")

namespace winsock
{
	Application::Application ( ) : handle_ { InitWinsock ( ) }
	{
	}

	bool Application::Initialized ( ) const noexcept
	{
		return bool { handle_ };
	}

	std::string Application::GetHostName ( ) const
	{
		char hostname [ 256 ];
		if ( gethostname ( hostname, sizeof ( hostname ) ) == SOCKET_ERROR )
		{
			const int error = WSAGetLastError ( );
			throw Exception { error };
		}

		return hostname;
	}

	Application::ComparableWSAData Application::InitWinsock ( )
	{
		WORD version = MAKEWORD ( 2, 2 );
		WSAData data { };
		const int error = WSAStartup ( version, &data );

		if ( error != NO_ERROR )
		{
			throw Exception { error };
		}
		return data;
	}
	Application::ComparableWSAData::ComparableWSAData ( ) noexcept : WSAData { }
	{
	}

	Application::ComparableWSAData::ComparableWSAData ( const WSAData& data ) noexcept : WSAData ( data )
	{
	}

	Application::ComparableWSAData::ComparableWSAData ( const ComparableWSAData& data ) noexcept : WSAData ( data )
	{
	}

	Application::ComparableWSAData::ComparableWSAData ( ComparableWSAData&& data ) noexcept : WSAData ( std::move ( data ) )
	{

	}

	Application::ComparableWSAData& Application::ComparableWSAData::operator=( const ComparableWSAData& data ) noexcept
	{
		WSAData& lhs = *this;
		lhs = data;

		return *this;
	}

	Application::ComparableWSAData& Application::ComparableWSAData::operator=( ComparableWSAData&& data ) noexcept
	{
		WSAData& lhs = *this;
		lhs = std::move ( data );

		return *this;
	}

	bool Application::ComparableWSAData::operator==( const WSAData& rhs ) const noexcept
	{
		return wVersion == rhs.wVersion;
	}

	bool Application::ComparableWSAData::operator!=( const WSAData& rhs ) const noexcept
	{
		return wVersion != rhs.wVersion;
	}

	void Application::Deleter::operator ( )( const pointer& pointer ) const noexcept
	{
		WSACleanup ( );
	}
}