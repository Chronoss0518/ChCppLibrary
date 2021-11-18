#ifndef Ch_CPP_Cmp_Run_h
#define Ch_CPP_Cmp_Run_h

#include"../ChBaseCompressor.h"

namespace ChCpp
{
	namespace Cmp
	{
		class CharactorRungless :public BaseCompressor
		{
		public:

			std::vector<unsigned char> Press(const std::vector<unsigned char>& _pressBase)override;

			std::vector<unsigned char> Thaw(const std::vector<unsigned char>& _thawBase)override;


		private:

			struct Memo
			{
				unsigned char datas = 0;
				unsigned long count = 0;
			};

		};

	}
}

#endif
