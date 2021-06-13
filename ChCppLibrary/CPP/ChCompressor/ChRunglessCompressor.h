#ifndef Ch_CPP_Cmp_Run_h
#define Ch_CPP_Cmp_Run_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	namespace Cmp
	{
		class Rungless :public BaseCompressor
		{
		public:

			std::vector<char> Press(const std::vector<char>& _pressBase)override;

			std::vector<char> Thaw(const std::vector<char>& _thawBase)override;

		private:

		};

	}
}

#endif
