#include"../../BaseIncluder/ChBase.h"
#include"ChNetWork.h"
#include"ChSockBase.h"
#include"ChInternetProtocol.h"

namespace ChCpp
{
	///////////////////////////////////////////////////////////////////////////////
	//Server���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	void Server::Init(const unsigned short _portNo)
	{

		//�A�h���X�t�@�~���̎w��
		addr.sin_family = AF_INET;

		//�T�[�o��IP�A�h���X
		//htonl:�l�b�g���[�N�o�C�g�I�[�_�[����z�X�g�o�C�g�I�[�_�[�֕ϊ�����//
		addr.sin_addr.s_addr = htonl(INADDR_ANY);

		//�T�[�o�̃|�[�g�ԍ�//
		//htons:�z�X�g�o�C�g�I�[�_�[����l�b�g���[�N�o�C�g�I�[�_�[�֕ϊ�����//
		addr.sin_port = htons(_portNo);
	}

	void Server::Release()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::SetLinkSocket(const std::vector<SOCKET>& _linkSock)
	{
		if (_linkSock.empty())return;

		if (!_linkSock.empty())
		{
			linkSock.clear();
		}

		linkSock = _linkSock;

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::Update()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Server::Link()
	{

	}


	///////////////////////////////////////////////////////////////////////////////
	//Client���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	void Client::Release()
	{

	}

	///////////////////////////////////////////////////////////////////////////////

	void Client::Link()
	{

	}

	///////////////////////////////////////////////////////////////////////////////
	//IP_TCP���\�b�h//
	///////////////////////////////////////////////////////////////////////////////

	bool IP_TCP::Init(NetWorkBase::SockBase* _base)
	{

		InternetProtocol::Init(_base);

		SOCKET test;

		test = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (test == SOCKET_ERROR)
		{
			ChFIO::OutToErrorText(
				"NetWorkProgrammError"
				, "�\�P�b�g�̐���(socket())�Ɏ��s���܂����B"
				, ChFIO::OTEAddType::AfterFirst);

			return false;
		}

		InsSocket(*_base);


		test = bind(InsSocket(
			*_base)
			, InsSockAddr(*_base)
			, sizeof(InsSockAddr_In(*_base)));


		if (test == SOCKET_ERROR)
		{
			ChFIO::OutToErrorText(
				"NetWorkProgrammError"
				, "�R�Â�(bind())�Ɏ��s���܂����B"
				, ChFIO::OTEAddType::AfterFirst);

			return false;
		}


		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	bool IP_TCP::Send(
		const std::string& _str)
	{
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	bool IP_TCP::Receve()
	{

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	std::string IP_TCP::TargetSend(
		const SOCKET& _targetSocket
		, const std::string& _str)
	{

		return "";
	}

	///////////////////////////////////////////////////////////////////////////////

	std::string IP_TCP::TargetReceve(
		const SOCKET& _targetSocket)
	{

		return "";
	}

	///////////////////////////////////////////////////////////////////////////////
	//IP_UDP���\�b�h//
	///////////////////////////////////////////////////////////////////////////////


	bool IP_UDP::Init(NetWorkBase::SockBase* _base)
	{

		InternetProtocol::Init(_base);



		SetInitFlg(true);
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	bool IP_UDP::Send(const std::string& _str)
	{

		return true;
	}

	///////////////////////////////////////////////////////////////////////////////

	bool IP_UDP::Receve()
	{

		return true;
	}

}