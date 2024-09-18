
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

#ifdef CRT
#include<thread>
#include<functional>
#endif

namespace ChCpp
{
	//void(void)の関数用マルチスレッドを実行するクラス//
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
		//マルチスレッドで動かしたい関数をセットする//
		void Init(const std::function<void(void)> _func);
#endif

		void Release();

	private:

		void CRTInit();

		void CRTRelease();

	public://IsFunction//

		//マルチスレッドで動いている関数が終わったかの判定//
		inline bool IsEndFunc() { return endFlg; }

	public://Other Functions//

		//マルチスレッドで動いている関数が終わるまで待つ//
		void Join();

		//同じ関数を再度走らせる//
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