

#ifndef Ch_CPP_CP_ForEx_h
#define Ch_CPP_CP_ForEx_h

namespace ChCp
{
	//継承して利用する//
	//拡張Forを作ることができる//
	template<class T>
	class ForEx
	{
	public:

		virtual T& Begin() = 0;

		virtual T& End() = 0;

	};

}

#endif
