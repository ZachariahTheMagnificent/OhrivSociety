#include "Exception.h"
#include <ws2tcpip.h>
#include <winsock2.h>

namespace winsock
{
	Exception::Type Exception::ErrorCodeToEnum ( const int error_code ) noexcept
	{
		//https://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx
		switch ( error_code )
		{
			case WSA_INVALID_HANDLE:
				return Type::INVALID_HANDLE;

			case WSA_NOT_ENOUGH_MEMORY:
				return Type::NOT_ENOUGH_MEMORY;

			case WSA_INVALID_PARAMETER:
				return Type::INVALID_PARAMETER;

			case WSA_OPERATION_ABORTED:
				return Type::OPERATION_ABORTED;

			case WSA_IO_INCOMPLETE:
				return Type::IO_INCOMPLETE;

			case WSA_IO_PENDING:
				return Type::IO_PENDING;

			case WSAEINTR:
				return Type::INTR;

			case WSAEBADF:
				return Type::BADF;

			case WSAEACCES:
				return Type::ACCES;

			case WSAEFAULT:
				return Type::FAULT;

			case WSAEINVAL:
				return Type::INVAL;

			case WSAEMFILE:
				return Type::MFILE;

			case WSAEWOULDBLOCK:
				return Type::WOULDBLOCK;

			case WSAEINPROGRESS:
				return Type::INPROGRESS;

			case WSAEALREADY:
				return Type::ALREADY;

			case WSAENOTSOCK:
				return Type::NOTSOCK;

			case WSAEDESTADDRREQ:
				return Type::DESTADDRREQ;

			case WSAEMSGSIZE:
				return Type::MSGSIZE;

			case WSAEPROTOTYPE:
				return Type::PROTOTYPE;

			case WSAENOPROTOOPT:
				return Type::NOPROTOOPT;

			case WSAEPROTONOSUPPORT:
				return Type::PROTONOSUPPORT;

			case WSAESOCKTNOSUPPORT:
				return Type::SOCKTNOSUPPORT;

			case WSAEOPNOTSUPP:
				return Type::OPNOTSUPP;

			case WSAEPFNOSUPPORT:
				return Type::PFNOSUPPORT;

			case WSAEAFNOSUPPORT:
				return Type::AFNOSUPPORT;

			case WSAEADDRINUSE:
				return Type::ADDRINUSE;

			case WSAEADDRNOTAVAIL:
				return Type::ADDRNOTAVAIL;

			case WSAENETDOWN:
				return Type::NETDOWN;

			case WSAENETUNREACH:
				return Type::NETUNREACH;

			case WSAENETRESET:
				return Type::NETRESET;

			case WSAECONNABORTED:
				return Type::CONNABORTED;

			case WSAECONNRESET:
				return Type::CONNRESET;

			case WSAENOBUFS:
				return Type::NOBUFS;

			case WSAEISCONN:
				return Type::ISCONN;

			case WSAENOTCONN:
				return Type::NOTCONN;

			case WSAESHUTDOWN:
				return Type::SHUTDOWN;

			case WSAETOOMANYREFS:
				return Type::TOOMANYREFS;

			case WSAETIMEDOUT:
				return Type::TIMEDOUT;

			case WSAECONNREFUSED:
				return Type::CONNREFUSED;

			case WSAELOOP:
				return Type::LOOP;

			case WSAENAMETOOLONG:
				return Type::NAMETOOLONG;

			case WSAEHOSTDOWN:
				return Type::HOSTDOWN;

			case WSAEHOSTUNREACH:
				return Type::HOSTUNREACH;

			case WSAENOTEMPTY:
				return Type::NOTEMPTY;

			case WSAEPROCLIM:
				return Type::PROCLIM;

			case WSAEUSERS:
				return Type::USERS;

			case WSAEDQUOT:
				return Type::DQUOT;

			case WSAESTALE:
				return Type::STALE;

			case WSAEREMOTE:
				return Type::REMOTE;

			case WSASYSNOTREADY:
				return Type::SYSNOTREADY;

			case WSAVERNOTSUPPORTED:
				return Type::VERNOTSUPPORTED;

			case WSANOTINITIALISED:
				return Type::NOTINITIALISED;

			case WSAEDISCON:
				return Type::DISCON;

			case WSAENOMORE:
				return Type::NO_MORE;

			case WSAECANCELLED:
				return Type::CANCELLED;

			case WSAEINVALIDPROCTABLE:
				return Type::INVALIDPROCTABLE;

			case WSAEINVALIDPROVIDER:
				return Type::INVALIDPROVIDER;

			case WSAEPROVIDERFAILEDINIT:
				return Type::PROVIDERFAILEDINIT;

			case WSASYSCALLFAILURE:
				return Type::SYSCALLFAILURE;

			case WSASERVICE_NOT_FOUND:
				return Type::SERVICE_NOT_FOUND;

			case WSATYPE_NOT_FOUND:
				return Type::TYPE_NOT_FOUND;

			case WSA_E_NO_MORE:
				return Type::NO_MORE;

			case WSA_E_CANCELLED:
				return Type::CANCELLED;

			case WSAEREFUSED:
				return Type::REFUSED;

			case WSAHOST_NOT_FOUND:
				return Type::HOSTNOTFOUND;

			case WSATRY_AGAIN:
				return Type::TRYAGAIN;

			case WSANO_RECOVERY:
				return Type::NORECOVERY;

			case WSANO_DATA:
				return Type::NODATA;

			case WSA_QOS_RECEIVERS:
				return Type::QOS_RECEIVERS;

			case WSA_QOS_SENDERS:
				return Type::QOS_SENDERS;

			case WSA_QOS_NO_SENDERS:
				return Type::QOS_NO_SENDERS;

			case WSA_QOS_NO_RECEIVERS:
				return Type::QOS_NO_RECEIVERS;

			case WSA_QOS_REQUEST_CONFIRMED:
				return Type::QOS_REQUEST_CONFIRMED;

			case WSA_QOS_ADMISSION_FAILURE:
				return Type::QOS_ADMISSION_FAILURE;

			case WSA_QOS_POLICY_FAILURE:
				return Type::QOS_POLICY_FAILURE;

			case WSA_QOS_BAD_STYLE:
				return Type::QOS_BAD_STYLE;

			case WSA_QOS_BAD_OBJECT:
				return Type::QOS_BAD_OBJECT;

			case WSA_QOS_TRAFFIC_CTRL_ERROR:
				return Type::QOS_TRAFFIC_CTRL_ERROR;

			case WSA_QOS_GENERIC_ERROR:
				return Type::QOS_GENERIC_ERROR;

			case WSA_QOS_ESERVICETYPE:
				return Type::QOS_ESERVICETYPE;

			case WSA_QOS_EFLOWSPEC:
				return Type::QOS_EFLOWSPEC;

			case WSA_QOS_EPROVSPECBUF:
				return Type::QOS_EPROVSPECBUF;

			case WSA_QOS_EFILTERSTYLE:
				return Type::QOS_EFILTERSTYLE;

			case WSA_QOS_EFILTERTYPE:
				return Type::QOS_EFILTERTYPE;

			case WSA_QOS_EFILTERCOUNT:
				return Type::QOS_EFILTERCOUNT;

			case WSA_QOS_EOBJLENGTH:
				return Type::QOS_EOBJLENGTH;

			case WSA_QOS_EFLOWCOUNT:
				return Type::QOS_EFLOWCOUNT;

			case WSA_QOS_EUNKOWNPSOBJ:
				return Type::QOS_EUNKOWNPSOBJ;

			case WSA_QOS_EPOLICYOBJ:
				return Type::QOS_EPOLICYOBJ;

			case WSA_QOS_EFLOWDESC:
				return Type::QOS_EFLOWDESC;

			case WSA_QOS_EPSFLOWSPEC:
				return Type::QOS_EPSFLOWSPEC;

			case WSA_QOS_EPSFILTERSPEC:
				return Type::QOS_EPSFILTERSPEC;

			case WSA_QOS_ESDMODEOBJ:
				return Type::QOS_ESDMODEOBJ;

			case WSA_QOS_ESHAPERATEOBJ:
				return Type::QOS_ESHAPERATEOBJ;

			case WSA_QOS_RESERVED_PETYPE:
				return Type::QOS_RESERVED_PETYPE;
		}

		return Type::NILL;
	}

	Exception::Exception ( const Type exception ) noexcept : error_ { exception }
	{
	}

	Exception::Exception ( const int error_code ) noexcept : error_ { ErrorCodeToEnum ( error_code ) }
	{
	}

	const char* Exception::what ( ) const noexcept
	{
		switch ( error_ )
		{
			case Type::INVALID_HANDLE:
				return "The application attempts to use an event object, but the specified handle is not valid.";

			case Type::NOT_ENOUGH_MEMORY:
				return "The application used a Windows Sockets function that directly maps to a Windows function.The Windows function is indicating a lack of required memory resources.";

			case Type::INVALID_PARAMETER:
				return "The application used a Windows Sockets function which directly maps to a Windows function.The Windows function is indicating a problem with one or more parameters.";

			case Type::OPERATION_ABORTED:
				return "The overlapped operation was canceled due to the closure of the socket, or the execution of the SIO_FLUSH command in WSAIoctl.";

			case Type::IO_INCOMPLETE:
				return "The application has tried to determine the status of an overlapped operation which is not yet completed. Applications that use WSAGetOverlappedResult(with the fWait flag set to FALSE) in a polling mode to determine when an overlapped operation has completed, get this error code until the operation is complete.";

			case Type::IO_PENDING:
				return "The application has initiated an overlapped operation that cannot be completed immediately. A completion indication will be given later when the operation has been completed.";

			case Type::INTR:
				return "The blocking operation was interrupted by a call to WSACancelBlockingCall.";

			case Type::BADF:
				return "The file handle supplied is not valid.";

			case Type::ACCES:
				return "The operation attempted to access a socket in a way forbidden by its access permissions. An example is using a broadcast address for sendto without broadcast permission being set using setsockopt(SO_BROADCAST). Another possible reason for the WSAEACCES error is that when the bind function is called(on Windows NT 4.0 with SP4 and later), another application, service, or kernel mode driver is bound to the same address with exclusive access. Such exclusive access is a new feature of Windows NT 4.0 with SP4 and later, and is implemented by using the SO_EXCLUSIVEADDRUSE option.";

			case Type::FAULT:
				return "The system detected an invalid pointer address in attempting to use a pointer argument of a call. This error occurs if an application passes an invalid pointer value, or if the length of the buffer is too small. For instance, if the length of an argument, which is a sockaddr structure, is smaller than the sizeof(sockaddr).";

			case Type::INVAL:
				return "Some invalid argument was supplied(for example, specifying an invalid level to the setsockopt function). In some instances, it also refers to the current state of the socket—for instance, calling accept on a socket that is not listening.";

			case Type::MFILE:
				return "Too many open sockets. Each implementation may have a maximum number of socket handles available, either globally, per process, or per thread.";

			case Type::WOULDBLOCK:
				return "This error is returned from operations on nonblocking sockets that cannot be completed immediately, for example recv when no data is queued to be read from the socket.It is a nonfatal error, and the operation should be retried later. It is normal for WSAEWOULDBLOCK to be reported as the result from calling connect on a nonblocking SOCK_STREAM socket, since some time must elapse for the connection to be established.";

			case Type::INPROGRESS:
				return "The blocking operation is currently executing. Windows Sockets only allows a single blocking operation per task or thread to be outstanding, and if any other function call is made(whether or not it references that or any other socket) the function fails with the WSAEINPROGRESS error.";

			case Type::ALREADY:
				return "The operation was attempted on a nonblocking socket with an operation already in progress—that is, calling connect a second time on a nonblocking socket that is already connecting, or canceling an asynchronous request(WSAAsyncGetXbyY) that has already been canceled or completed.";

			case Type::NOTSOCK:
				return "The operation was attempted on something that is not a socket. Either the socket handle parameter did not reference a valid socket, or for select, a member of an fd_set was not valid.";

			case Type::DESTADDRREQ:
				return "A required address was omitted from an operation on a socket. For example, this error is returned if sendto is called with the remote address of ADDR_ANY.";

			case Type::MSGSIZE:
				return "A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.";

			case Type::PROTOTYPE:
				return "A protocol was specified in the socket function call that does not support the semantics of the socket type requested. For example, the ARPA Internet UDP protocol cannot be specified with a socket type of SOCK_STREAM.";

			case Type::NOPROTOOPT:
				return "An unknown, invalid or unsupported option or level was specified in a getsockopt or setsockopt call.";

			case Type::PROTONOSUPPORT:
				return "The requested protocol has not been configured into the system, or no implementation for it exists. For example, a socket call requests a SOCK_DGRAM socket, but specifies a stream protocol.";

			case Type::SOCKTNOSUPPORT:
				return "The support for the specified socket type does not exist in this address family. For example, the optional type SOCK_RAW might be selected in a socket call, and the implementation does not support SOCK_RAW sockets at all.";

			case Type::OPNOTSUPP:
				return "The attempted operation is not supported for the type of object referenced. Usually this occurs when a socket descriptor to a socket that cannot support this operation is trying to accept a connection on a datagram socket.";

			case Type::PFNOSUPPORT:
				return "The protocol family has not been configured into the system or no implementation for it exists. This message has a slightly different meaning from WSAEAFNOSUPPORT.However, it is interchangeable in most cases, and all Windows Sockets functions that return one of these messages also specify WSAEAFNOSUPPORT.";

			case Type::AFNOSUPPORT:
				return "An address incompatible with the requested protocol was used. All sockets are created with an associated address family(that is, AF_INET for Internet Protocols) and a generic protocol type(that is, SOCK_STREAM). This error is returned if an incorrect protocol is explicitly requested in the socket call, or if an address of the wrong family is used for a socket, for example, in sendto.";

			case Type::ADDRINUSE:
				return "Typically, only one usage of each socket address(protocol / IP address / port) is permitted. This error occurs if an application attempts to bind a socket to an IP address / port that has already been used for an existing socket, or a socket that was not closed properly, or one that is still in the process of closing. For server applications that need to bind multiple sockets to the same port number, consider using setsockopt(SO_REUSEADDR). Client applications usually need not call bind at all—connect chooses an unused port automatically.When bind is called with a wildcard address(involving ADDR_ANY), a WSAEADDRINUSE error could be delayed until the specific address is committed.This could happen with a call to another function later, including connect, listen, WSAConnect, or WSAJoinLeaf.";

			case Type::ADDRNOTAVAIL:
				return "The requested address is not valid in its context. This normally results from an attempt to bind to an address that is not valid for the local computer. This can also result from connect, sendto, WSAConnect, WSAJoinLeaf, or WSASendTo when the remote address or port is not valid for a remote computer(for example, address or port 0).";

			case Type::NETDOWN:
				return "The socket operation encountered a dead network. This could indicate a serious failure of the network system(that is, the protocol stack that the Windows Sockets DLL runs over), the network interface, or the local network itself.";

			case Type::NETUNREACH:
				return "The socket operation was attempted to an unreachable network. This usually means the local software knows no route to reach the remote host.";

			case Type::NETRESET:
				return "The connection has been broken due to keep - alive activity detecting a failure while the operation was in progress. It can also be returned by setsockopt if an attempt is made to set SO_KEEPALIVE on a connection that has already failed.";

			case Type::CONNABORTED:
				return "An established connection was aborted by the software in your host computer, possibly due to a data transmission timeout or protocol error.";

			case Type::CONNRESET:
				return "An existing connection was forcibly closed by the remote host. This normally results if the peer application on the remote host is suddenly stopped, the host is rebooted, the host or remote network interface is disabled, or the remote host uses a hard close(see setsockopt for more information on the SO_LINGER option on the remote socket). This error may also result if a connection was broken due to keep-alive activity detecting a failure while one or more operations are in progress. Operations that were in progress fail with Type::NETRESET. Subsequent operations fail with Type::CONNRESET.";

			case Type::NOBUFS:
				return "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";

			case Type::ISCONN:
				return "A connect request was made on an already-connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket(for SOCK_STREAM sockets, the to parameter in sendto is ignored) although other implementations treat this as a legal occurrence.";

			case Type::NOTCONN:
				return "A request to send or receive data was disallowed because the socket is not connected and(when sending on a datagram socket using sendto) no address was supplied. Any other type of operation might also return this error—for example, setsockopt setting SO_KEEPALIVE if the connection has been reset.";

			case Type::SHUTDOWN:
				return "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. By calling shutdown a partial close of a socket is requested, which is a signal that sending or receiving, or both have been discontinued.";

			case Type::TOOMANYREFS:
				return "Too many references to some kernel object.";

			case Type::TIMEDOUT:
				return "A connection attempt failed because the connected party did not properly respond after a period of time, or the established connection failed because the connected host has failed to respond.";

			case Type::CONNREFUSED:
				return "No connection could be made because the target computer actively refused it.This usually results from trying to connect to a service that is inactive on the foreign host—that is, one with no server application running.";

			case Type::LOOP:
				return "Cannot translate a name.";

			case Type::NAMETOOLONG:
				return "A name component or a name was too long.";

			case Type::HOSTDOWN:
				return "The socket operation failed because the destination host is down. The socket operation encountered a dead host. Networking activity on the local host has not been initiated. These conditions are more likely to be indicated by the error Type::TIMEDOUT.";

			case Type::HOSTUNREACH:
				return "A socket operation was attempted to an unreachable host.See Type::NETUNREACH.";

			case Type::NOTEMPTY:
				return "Cannot remove a directory that is not empty.";

			case Type::PROCLIM:
				return "A Windows Sockets implementation may have a limit on the number of applications that can use it simultaneously. WSAStartup may fail with this error if the limit has been reached.";

			case Type::USERS:
				return "Ran out of user quota.";

			case Type::DQUOT:
				return "Ran out of disk quota.";

			case Type::STALE:
				return "The file handle reference is no longer available.";

			case Type::REMOTE:
				return "The item is not available locally.";

			case Type::SYSNOTREADY:
				return "This error is returned by WSAStartup if the Windows Sockets implementation cannot function at this time because the underlying system it uses to provide network services is currently unavailable. Users should check : that the appropriate Windows Sockets DLL file is in the current path, that they are not trying to use more than one Windows Sockets implementation simultaneously(If there is more than one Winsock DLL on your system, be sure the first one in the path is appropriate for the network subsystem currently loaded), the Windows Sockets implementation documentation to be sure all necessary components are currently installed and configured correctly.";

			case Type::VERNOTSUPPORTED:
				return "The current Windows Sockets implementation does not support the Windows Sockets specification version requested by the application.Check that no old Windows Sockets DLL files are being accessed.";

			case Type::NOTINITIALISED:
				return "Either the application has not called WSAStartup or WSAStartup failed.The application may be accessing a socket that the current active task does not own(that is, trying to share a socket between tasks), or WSACleanup has been called too many times.";

			case Type::DISCON:
				return "Thrown by WSARecv and WSARecvFrom to indicate that the remote party has initiated a graceful shutdown sequence.";

			case Type::INVALIDPROCTABLE:
				return "The service provider procedure call table is invalid.A service provider returned a bogus procedure table to Ws2_32.dll.This is usually caused by one or more of the function pointers being NULL.";

			case Type::INVALIDPROVIDER:
				return "The requested service provider is invalid.This error is returned by the WSCGetProviderInfo and WSCGetProviderInfo32 functions if the protocol entry specified could not be found.This error is also returned if the service provider returned a version number other than 2.0.";

			case Type::PROVIDERFAILEDINIT:
				return "The requested service provider could not be loaded or initialized.This error is returned if either a service provider's DLL could not be loaded (LoadLibrary failed) or the provider's WSPStartup or NSPStartup function failed.";

			case Type::SYSCALLFAILURE:
				return "A system call that should never fail has failed.This is a generic error code, returned under various conditions: Returned when a system call that should never fail does fail(For example, if a call to WaitForMultipleEvents fails or one of the registry functions fails trying to manipulate the protocol / namespace catalogs), Returned when a provider does not return SUCCESS and does not provide an extended error code(Can indicate a service provider implementation error)";

			case Type::SERVICE_NOT_FOUND:
				return "No such service is known.The service cannot be found in the specified name space.";

			case Type::TYPE_NOT_FOUND:
				return "The specified class was not found.";

			case Type::NO_MORE:
				return "No more results can be returned by the Type::LookupServiceNext function.";

			case Type::CANCELLED:
				return "A call to the Type::LookupServiceEnd function was made while this call was still processing. The call has been canceled.";

			case Type::REFUSED:
				return "The database query failed because it was actively refused.";

			case Type::HOSTNOTFOUND:
				return "No such host is known.The name is not an official host name or alias, or it cannot be found in the database(s) being queried. This error may also be returned for protocol and service queries, and means that the specified name could not be found in the relevant database.";

			case Type::TRYAGAIN:
				return "This is usually a temporary error during host name resolution and means that the local server did not receive a response from an authoritative server. A retry at some time later may be successful.";

			case Type::NORECOVERY:
				return "This indicates that some sort of nonrecoverable error occurred during a database lookup. This may be because the database files(for example, BSD - compatible HOSTS, SERVICES, or PROTOCOLS files) could not be found, or a DNS request was returned by the server with a severe error.";

			case Type::NODATA:
				return "The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for. The usual example for this is a host name-to-address translation attempt(using gethostbyname or WSAAsyncGetHostByName) which uses the DNS(Domain Name Server). An MX record is returned but no A record—indicating the host itself exists, but is not directly reachable.";

			case Type::QOS_RECEIVERS:
				return "At least one QoS reserve has arrived.";

			case Type::QOS_SENDERS:
				return "At least one QoS send path has arrived.";

			case Type::QOS_NO_SENDERS:
				return "There are no QoS senders.";

			case Type::QOS_NO_RECEIVERS:
				return "There are no QoS receivers.";

			case Type::QOS_REQUEST_CONFIRMED:
				return "The QoS reserve request has been confirmed.";

			case Type::QOS_ADMISSION_FAILURE:
				return "A QoS error occurred due to lack of resources.";

			case Type::QOS_POLICY_FAILURE:
				return "The QoS request was rejected because the policy system couldn't allocate the requested resource within the existing policy.";

			case Type::QOS_BAD_STYLE:
				return "An unknown or conflicting QoS style was encountered.";

			case Type::QOS_BAD_OBJECT:
				return "A problem was encountered with some part of the filterspec or the provider - specific buffer in general.";

			case Type::QOS_TRAFFIC_CTRL_ERROR:
				return "An error with the underlying traffic control(TC) API as the generic QoS request was converted for local enforcement by the TC API. This could be due to an out of memory error or to an internal QoS provider error.";

			case Type::QOS_GENERIC_ERROR:
				return "A general QoS error.";

			case Type::QOS_ESERVICETYPE:
				return "An invalid or unrecognized service type was found in the QoS flowspec.";

			case Type::QOS_EFLOWSPEC:
				return "An invalid or inconsistent flowspec was found in the QOS structure.";

			case Type::QOS_EPROVSPECBUF:
				return "An invalid QoS provider-specific buffer.";

			case Type::QOS_EFILTERSTYLE:
				return "An invalid QoS filter style was used.";

			case Type::QOS_EFILTERTYPE:
				return "An invalid QoS filter type was used.";

			case Type::QOS_EFILTERCOUNT:
				return "An incorrect number of QoS FILTERSPECs were specified in the FLOWDESCRIPTOR.";

			case Type::QOS_EOBJLENGTH:
				return "An object with an invalid ObjectLength field was specified in the QoS provider-specific buffer.";

			case Type::QOS_EFLOWCOUNT:
				return "An incorrect number of flow descriptors was specified in the QoS structure.";

			case Type::QOS_EUNKOWNPSOBJ:
				return "An unrecognized object was found in the QoS provider-specific buffer.";

			case Type::QOS_EPOLICYOBJ:
				return "An invalid policy object was found in the QoS provider-specific buffer.";

			case Type::QOS_EFLOWDESC:
				return "An invalid QoS flow descriptor was found in the flow descriptor list.";

			case Type::QOS_EPSFLOWSPEC:
				return "An invalid or inconsistent flowspec was found in the QoS provider-specific buffer.";

			case Type::QOS_EPSFILTERSPEC:
				return "An invalid FILTERSPEC was found in the QoS provider-specific buffer.";

			case Type::QOS_ESDMODEOBJ:
				return "An invalid shape discard mode object was found in the QoS provider-specific buffer.";

			case Type::QOS_ESHAPERATEOBJ:
				return "An invalid shaping rate object was found in the QoS provider-specific buffer.";

			case Type::QOS_RESERVED_PETYPE:
				return "A reserved policy element was found in the QoS provider-specific buffer.";
		}

		return "lol I dunno.";
	}

	Exception::Type Exception::GetType ( ) const noexcept
	{
		return error_;
	}
}