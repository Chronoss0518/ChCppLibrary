

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

		virtual T& Begin() = 0;

		virtual T& End() = 0;

	};

}

#endif
