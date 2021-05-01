
#ifndef Ch_CPP_Sock_h
#define Ch_CPP_Sock_h

#ifdef _WIN32

#include<Windows.h>
#include<winsock.h>

using socklen_t = int;

#elif __linux__

#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet>

#define closesocket(sock) close(sock)
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
using SOCKET = int;

#endif

#include"ChNetWork.h"
#include"ChInternetProtocol.h"

namespace ChCpp
{

	class Server :public NetWorkBase::SockBase
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const unsigned short _portNo)override;

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////
		//GetFunction//

		inline std::vector<SOCKET> GetLinsSocket() { return linkSock; }

		///////////////////////////////////////////////////////////////////////////////
		//SetFunction//

		void SetLinkSocket(const std::vector<SOCKET>& _linkSock);

		///////////////////////////////////////////////////////////////////////////////
		//UpdateFunction//

		void Update()override;

		///////////////////////////////////////////////////////////////////////////////

		void Link()override;

	private:

		std::vector<SOCKET>linkSock;
		int linkCount = 0;

	};

	class Client :public NetWorkBase::SockBase
	{

	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual void Init(const unsigned short _portNo)override;

		void Release()override;

		///////////////////////////////////////////////////////////////////////////////

		void Link()override;

	private:

		SOCKET linkSock{ 0 };

	};

}


#endif