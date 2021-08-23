#ifndef Ch_CPP_Cmp_Base_h
#define Ch_CPP_Cmp_Base_h

namespace ChCpp
{
	namespace Cmp
	{
		 class BaseCompressor
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			
			//à≥èkä÷êî//
			virtual std::vector<unsigned char> Press(const std::vector<unsigned char>& _pressBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

			//âìÄä÷êî//
			virtual std::vector<unsigned char> Thaw(const std::vector<unsigned char>& _thawBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

		};

	}
}

#endif
