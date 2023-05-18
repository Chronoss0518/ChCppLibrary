
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

namespace std
{
	class thread;
}

namespace ChCpp
{
	//void(void)の関数用マルチスレッドを実行するクラス//
	class MultiThread :public ChCp::Initializer
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		MultiThread() {}

		MultiThread(const std::function<void(void)> _func);

		~MultiThread() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//マルチスレッドで動かしたい関数をセットする//
		void Init(const std::function<void(void)> _func);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//マルチスレッドで動いている関数が終わったかの判定//
		bool IsEndFunc() { return endFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//マルチスレッドで動いている関数が終わるまで待つ//
		void Join();

		//同じ関数を再度走らせる//
		void ReRun();

	protected:

		void Function();

		std::thread thread;

		std::function<void(void)> func = nullptr;

		bool endFlg = true;

	};


}

#endif