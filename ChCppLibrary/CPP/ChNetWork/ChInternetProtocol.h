
#ifndef Ch_CPP_IP_h
#define Ch_CPP_IP_h

#ifdef _WINDOWS

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
#include"ChSockBase.h"

namespace ChCpp
{

	class IP_TCP :public NetWorkBase::InternetProtocol
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual bool Init(NetWorkBase::SockBase* _base)override;

		///////////////////////////////////////////////////////////////////////////////
		//CommunityFunction//

		 bool Send(
			const std::string& _str)override;

		 bool Receve()override;

		 std::string TargetSend(
			const SOCKET& _targetSocket
			, const std::string& _str);

		 std::string TargetReceve(
			const SOCKET& _targetSocket);
	};

	class IP_UDP :public NetWorkBase::InternetProtocol
	{
	public:

		///////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		virtual bool Init(NetWorkBase::SockBase* _base)override;

		///////////////////////////////////////////////////////////////////////////////
		//CommunityFunction//

		bool Send(
			const std::string& _str)override;

		bool Receve()override;

		virtual bool CustomSend();

	};

}

#endif