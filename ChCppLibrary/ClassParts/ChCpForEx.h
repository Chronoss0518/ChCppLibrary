

#ifndef Ch_CPP_CP_ForEx_h
#define Ch_CPP_CP_ForEx_h

namespace ChCp
{
	//Œp³‚µ‚Ä—˜—p‚·‚é//
	//Šg’£For‚ğì‚é‚±‚Æ‚ª‚Å‚«‚é//
	template<class T>
	class ForEx
	{
	public:

		virtual T& Begin() = 0;

		virtual T& End() = 0;

	};

}

#endif
