
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

#ifdef CRT
#include<thread>
#include<functional>
#endif

namespace ChCpp
{
	//void(void)�̊֐��p�}���`�X���b�h�����s����N���X//
	class MultiThread :public ChCp::Initializer
	{
	public://ConstructerDestructer//

		MultiThread() {}

#ifdef CRT
		MultiThread(const std::function<void(void)> _func);
#endif

		~MultiThread() { Release(); }
	public://InitAndRelease//

#ifdef CRT
		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _func);
#endif

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
#ifdef CRT
		std::thread thread;
		std::function<void(void)> func = nullptr;
#endif
	};
}

#ifdef CRT

ChCpp::MultiThread::MultiThread(const std::function<void(void)> _func) { Init(_func); }

void ChCpp::MultiThread::Init(const std::function<void(void)> _func)
{
	if (!endFlg)return;

	if (thread.joinable())
		thread.detach();

	func = _func;

	ReRun();

	SetInitFlg(true);
}

void ChCpp::MultiThread::ReRun()
{
	if (!endFlg)return;

	endFlg = false;

	thread = std::thread([&] {Function(); });

}

void ChCpp::MultiThread::Release()
{
	if (!IsInit())return;

	if (!thread.joinable())return;

	thread.join();

	SetInitFlg(false);
}

void ChCpp::MultiThread::Join() { thread.join(); }

void ChCpp::MultiThread::Function()
{
	func();

	endFlg = true;
}


#endif

#endif