
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
	public://ConstructerDestructer//

		MultiThread() {}

#ifdef CRT
		MultiThread(const std::function<void(void)> _func);
#endif

		~MultiThread() { Release(); }
	public://InitAndRelease//

#ifdef CRT
		//マルチスレッドで動かしたい関数をセットする//
		void Init(const std::function<void(void)> _func);
#endif

		void Release();

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