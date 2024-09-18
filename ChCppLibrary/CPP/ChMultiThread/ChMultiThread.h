
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
	public:

		struct MultiThreadCRT
		{
#ifdef CRT
			std::thread thread;
			std::function<void(void)> func = nullptr;
#endif
		};

	public://ConstructerDestructer//

		MultiThread() { CRTInit(); }

#ifdef CRT
		MultiThread(const std::function<void(void)> _func);
#endif

		~MultiThread()
		{
			Release();
			CRTRelease();
		}

	public://InitAndRelease//

#ifdef CRT
		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _func);
#endif

		void Release();

	private:

		void CRTInit();

		void CRTRelease();

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

		MultiThreadCRT& ValueIns() { return *value; }

	private:

		MultiThreadCRT* value = nullptr;

	};
}

#ifdef CRT

void ChCpp::MultiThread::CRTInit()
{
	value = new MultiThreadCRT();
}

void ChCpp::MultiThread::CRTRelease()
{
	delete value;
}

ChCpp::MultiThread::MultiThread(const std::function<void(void)> _func)
{
	CRTInit();
	Init(_func);
}

void ChCpp::MultiThread::Init(const std::function<void(void)> _func)
{
	if (!endFlg)return;

	if (ValueIns().thread.joinable())
		ValueIns().thread.detach();

	ValueIns().func = _func;

	ReRun();

	SetInitFlg(true);
}

void ChCpp::MultiThread::ReRun()
{
	if (!endFlg)return;

	endFlg = false;

	ValueIns().thread = std::thread([&] {Function(); });

}

void ChCpp::MultiThread::Release()
{
	if (!IsInit())return;

	if (!ValueIns().thread.joinable())return;

	ValueIns().thread.join();

	SetInitFlg(false);
}

void ChCpp::MultiThread::Join() { ValueIns().thread.join(); }

void ChCpp::MultiThread::Function()
{
	ValueIns().func();

	endFlg = true;
}


#endif

#endif