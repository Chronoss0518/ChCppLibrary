

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

		virtual T& begin() = 0;

		virtual T& end() = 0;

	};

}

#endif
