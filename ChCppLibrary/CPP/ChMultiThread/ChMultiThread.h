
#ifndef Ch_CPP_MuTh_h
#define Ch_CPP_MuTh_h

namespace std
{
	class thread;
}

namespace ChCpp
{
	//void(void)�̊֐��p�}���`�X���b�h�����s����N���X//
	class ChMultiThread
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////
		//ConstructerDestructer//

		ChMultiThread() {}

		ChMultiThread(const std::function<void(void)> _func);

		~ChMultiThread() { Release(); }

		///////////////////////////////////////////////////////////////////////////////////
		//InitAndRelease//

		//�}���`�X���b�h�œ����������֐����Z�b�g����//
		void Init(const std::function<void(void)> _func);

		void Release();

		///////////////////////////////////////////////////////////////////////////////////
		//IsFunction//

		//�}���`�X���b�h�œ����Ă���֐����I��������̔���//
		ChStd::Bool IsEndFunc() { return endFlg; }

		///////////////////////////////////////////////////////////////////////////////////

		//�}���`�X���b�h�œ����Ă���֐����I���܂ő҂�//
		void Join();

		//�����֐����ēx���点��//
		void ReRun();

	protected:

		void Function();

		std::thread thread;

		std::function<void(void)> func = nullptr;

		ChStd::Bool endFlg = true;

	};


}

#endif