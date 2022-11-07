
#include"../../BaseIncluder/ChBase.h"

#include<thread>
#include"ChMultiThread.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChMUltThreadÉÅÉ\ÉbÉh//
///////////////////////////////////////////////////////////////////////////////////

ChMultiThread::ChMultiThread(const std::function<void(void)> _func)
{
	Init(_func);
}

void ChMultiThread::Init(const std::function<void(void)> _func)
{
	if (!endFlg)return;

	if (thread.joinable())
	{
		thread.detach();
	}
	func = _func;

	ReRun();
}

void ChMultiThread::ReRun()
{
	if (!endFlg)return;

	endFlg = false;

	thread = std::thread([&] {Function(); });

}

void ChMultiThread::Release()
{
	if (!thread.joinable())return;

	thread.join();
	
}

void ChMultiThread::Join()
{
	thread.join();
}

void ChMultiThread::Function()
{
	func();

	endFlg = true;
}
