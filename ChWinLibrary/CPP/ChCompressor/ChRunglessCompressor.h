#ifndef Ch_CPP_Cmp_Run_h
#define Ch_CPP_Cmp_Run_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	namespace Cmp
	{
		 class Rungless:public BaseComp
		{
		public:

			std::string Press(const std::string& _pressBase)override;

			std::string Thaw(const std::string& _thawBase)override;

		private:

			

		};


		 using Rung = Rungless;
	}
}

#endif
