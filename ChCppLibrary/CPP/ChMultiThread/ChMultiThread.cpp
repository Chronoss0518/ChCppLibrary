#include"ChMultiThread.h"


ChCpp::MultiThread::MultiThread(const std::function<void(void)> _func)
{
	Init(_func);
}

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
