
#include"../../BaseIncluder/ChBase.h"

#include<thread>
#include"ChMultiThread.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////
//ChMUltThread���\�b�h//
///////////////////////////////////////////////////////////////////////////////////

ChMultiThread::ChMultiThread(const std::function<void(void)> _func)
{
	Init(_func);
}

void ChMultiThread::Init(const std::function<void(void)> _func)
{
	if (thread.joinable())
	{
		thread.detach();
	}
	func = _func;

	endFlg = false;

	thread = std::thread([this] {Function(); });
	
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
