

#ifndef Ch_CPP_CP_ForEx_h
#define Ch_CPP_CP_ForEx_h

namespace ChCp
{
	//�p�����ė��p����//
	//�g��For����邱�Ƃ��ł���//
	template<class T>
	class ForEx
	{
	public:

		virtual T& begin() = 0;

		virtual T& end() = 0;

	};

}

#endif
