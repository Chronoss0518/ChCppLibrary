#ifndef Ch_CPP_Cmp_Def_h
#define Ch_CPP_Cmp_Def_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	class BitBool;

	namespace Cmp
	{

		class Deflate :public BaseCompressor
		{
		public:

			std::vector<char> Press(const std::vector<char>& _pressBase)override;

			std::vector<char> Thaw(const std::vector<char>& _thawBase)override;

		private:



		};
	}
}

#endif
