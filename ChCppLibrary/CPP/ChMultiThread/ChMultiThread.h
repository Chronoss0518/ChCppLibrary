
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

namespace std
{
	class thread;
}

namespace ChCpp
{
	//void(void)�̊֐��p�}���`�X���b�h�����s����N���X//
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

		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _func);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�}���`�X���b�h�œ����Ă���֐����I��������̔���//
		bool IsEndFunc() { return endFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�}���`�X���b�h�œ����Ă���֐����I���܂ő҂�//
		void Join();

		//�����֐����ēx���点��//
		void ReRun();

	protected:

		void Function();

		std::thread thread;

		std::function<void(void)> func = nullptr;

		bool endFlg = true;

	};


}

#endif