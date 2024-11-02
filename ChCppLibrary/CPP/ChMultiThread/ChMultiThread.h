
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

#include<thread>
#include<functional>

#include"../../ClassParts/ChCPInitializer.h"

namespace ChCpp
{
	//void(void)の関数用マルチスレッドを実行するクラス//
	class MultiThread :public ChCp::Initializer
	{
	public://ConstructerDestructer//

		MultiThread() {}

		MultiThread(const std::function<void(void)> _func);

		~MultiThread() { Release(); }

	public://InitAndRelease//

		//マルチスレッドで動かしたい関数をセットする//
		void Init(const std::function<void(void)> _func);

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

		std::thread thread;
		std::function<void(void)> func = nullptr;
	};
}

#endif