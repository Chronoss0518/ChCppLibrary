
#ifndef Ch_CPP_NWork_h
#define Ch_CPP_NWork_h

#ifdef _WIN32

#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"wsock32.lib")

using socklen_t = int;

#elif _WIN64


#include<Windows.h>
#include<winsock.h>
#pragma comment(lib,"wsock32.lib")

using socklen_t = int;

#else

#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet>

#define closesocket(sock) close(sock)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

#endif

namespace ChCpp
{
	class NetWork;
	class Server;
	class Client;

	class IP_TCP;
	class IP_UDP;

	class NetWorkBase
	{
	public:

		friend NetWork;

		friend Server;
		friend Client;

		friend IP_TCP;
		friend IP_UDP;

	private:
		
		class InternetProtocol;

		class SockBase :public ChCp::Initializer,public ChCp::Releaser
		{
		public:

			friend InternetProtocol;


			///////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			virtual void Init(const unsigned short _portNo = 49152) = 0;

			virtual void Release()override
			{
				if (!(*this))return;
				closesocket(baseSock);
				SetInitFlg(false);
			}

			virtual ChStd::Bool InitPropaty(const int _maxLinkCount) = 0;

			///////////////////////////////////////////////////////////////////////////////
			//SetFunction//

			///////////////////////////////////////////////////////////////////////////////
			//GetFunction//

			const SOCKET GetbaseSocket() const { return baseSock; }

			const sockaddr* GetAddr() { return reinterpret_cast<sockaddr*>(&addr); }

			///////////////////////////////////////////////////////////////////////////////
			//UpdateFunction//

			virtual void Update() {};

			///////////////////////////////////////////////////////////////////////////////

			virtual void Link() = 0;

		protected:

			SOCKET baseSock{ 0 };

			sockaddr_in addr{ 0 };

		};

		class InternetProtocol :public ChCp::Initializer
		{
		public:

			///////////////////////////////////////////////////////////////////////////////
			//ConstructerDestructer//

			virtual ~InternetProtocol() {}

			///////////////////////////////////////////////////////////////////////////////
			//InitAndRelease//

			inline virtual ChStd::Bool Init(SockBase* _base)
			{
				if (ChPtr::NullCheck(_base))return false;
				targetSocket = _base;
				return true;
			}

			///////////////////////////////////////////////////////////////////////////////
			//CommunityFunction//

			virtual ChStd::Bool Send(
				const std::string& _str) = 0;

			virtual ChStd::Bool Receve() = 0;

			inline virtual void Release()
			{
				if (!(*this))return;
				SetInitFlg(false);
			}

		protected:

			//SocketBase?????x?[?X???????\?P?b?g??????//
			SOCKET& InsSocketFromSockBase(SockBase& _sock)
			{
				return _sock.baseSock;
			}

			//InsSocketFromSockBase????????//
			SOCKET& InsSocket(SockBase& _sock)
			{
				return _sock.baseSock;
			}

			//SocketBase????SockAddr??????//
			sockaddr_in& InsSockAddrFromSockBase_In(SockBase& _sock)
			{
				return _sock.addr;
			}

			//InsSockAddrFromSockBase????????//
			sockaddr_in& InsSockAddr_In(SockBase& _sock)
			{
				return _sock.addr;
			}

			//SocketBase????SockAddr??????//
			sockaddr* InsSockAddrFromSockBase(SockBase& _sock)
			{
				return reinterpret_cast<sockaddr*>(&_sock.addr);
			}

			//InsSockAddrFromSockBase????????//
			sockaddr* InsSockAddr(SockBase& _sock)
			{
				return reinterpret_cast<sockaddr*>(&_sock.addr);
			}

			std::vector<std::string>receveStrs;

		private:

			SockBase* targetSocket = nullptr;

		};

	};

	class NetWork
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//
		template<class IP, class Sock>
		auto Init(const int _MaxLinkCount = 1)->typename std::enable_if
			<std::is_base_of<NetWorkBase::InternetProtocol, IP>::value &&
			(std::is_base_of<Server, Sock>::value
				|| std::is_same<Server, Sock>::value), void>::type
		{
			if (_MaxLinkCount <= 0)return;

			WinInit();

			sock = new Sock();

			sock->Init();

			ip = new IP();

			if (!ip->Init(sock))
			{
				return;
			}

		}

		template<class IP, class Sock>
		auto Init()->typename std::enable_if
			<std::is_base_of<NetWorkBase::InternetProtocol, IP>::value &&
			(std::is_base_of<Client, Sock>::value
				|| std::is_same<Client, Sock>::value), void>::type
		{

			WinInit();

			sock = new Sock();

			sock->Init();

			ip = new IP();

			if (!ip->Init(sock))
			{
				return;
			}

		}

		void Release();

		///////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		///////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		template<class Sock>
		auto GetSock()->typename std::enable_if
			<std::is_base_of<NetWorkBase::SockBase, Sock>::value, Sock*>::type
		{ return ChPtr::SafeCast<Sock*>(sock); }

		template<class IP>
		auto GetIP()->typename std::enable_if
			<std::is_base_of<NetWorkBase::InternetProtocol, IP>::value, IP*>::type 
		{ return ChPtr::SafeCast<IP*>(ip); }

		///////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update();

	protected:

		inline ChStd::Bool WinInit()
		{

#ifdef _WINDOWS_
			//WisSockVer//
			WORD wVerReq = MAKEWORD(1, 1);
			//???C?u????????????????????????//
			WSADATA wsadata{ 0 };
			{
				if (WSAStartup(wVerReq, &wsadata) != 0)
				{
					//?????????????????G???[???N????//
					//throw "WSAStartup()";
					return false;
				}
			}
#endif

			return true;
		}

		inline void WinRelease()
		{

#ifdef _WINDOWS_
			WSACleanup();
#endif

		}

	private:

		NetWorkBase::InternetProtocol* ip;
		NetWorkBase::SockBase* sock;

	};

}


#endif