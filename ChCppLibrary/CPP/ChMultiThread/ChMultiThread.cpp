
#include"../../BaseIncluder/ChBase.h"

#include<thread>
#include"ChMultiThread.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChMUltThreadÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

MultiThread::MultiThread(const std::function<void(void)> _func)
{
	Init(_func);
}

void MultiThread::Init(const std::function<void(void)> _func)
{
	if (!endFlg)return;

	if (thread.joinable())
	{
		thread.detach();
	}
	func = _func;

	ReRun();

	SetInitFlg(true);
}

void MultiThread::ReRun()
{
	if (!endFlg)return;

	endFlg = false;

	thread = std::thread([&] {Function(); });

}

void MultiThread::Release()
{
	if (!IsInit())return;

	if (!thread.joinable())return;

	thread.join();

	SetInitFlg(false);
}

void MultiThread::Join()
{
	thread.join();
}

void MultiThread::Function()
{
	func();

	endFlg = true;
}
