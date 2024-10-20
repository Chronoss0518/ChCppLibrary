
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

#include<thread>
#include<functional>

#include"../../ClassParts/ChCPInitializer.h"

namespace ChCpp
{
	//void(void)�̊֐��p�}���`�X���b�h�����s����N���X//
	class MultiThread :public ChCp::Initializer
	{
	public://ConstructerDestructer//

		MultiThread() {}

		MultiThread(const std::function<void(void)> _func);

		~MultiThread() { Release(); }

	public://InitAndRelease//

		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _func);

		void Release();

	public://IsFunction//

		//�}���`�X���b�h�œ����Ă���֐����I��������̔���//
		inline bool IsEndFunc() { return endFlg; }

	public://Other Functions//

		//�}���`�X���b�h�œ����Ă���֐����I���܂ő҂�//
		void Join();

		//�����֐����ēx���点��//
		void ReRun();

	protected://Other Functions//

		void Function();

	protected://Member Value//

		bool endFlg = true;

		std::thread thread;
		std::function<void(void)> func = nullptr;
	};
}

#endif