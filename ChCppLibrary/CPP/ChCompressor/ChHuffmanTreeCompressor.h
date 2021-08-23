#ifndef Ch_CPP_Cmp_Huf_h
#define Ch_CPP_Cmp_Huf_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	class BitBool;

	namespace Cmp
	{

		class HuffmanTree :public BaseCompressor
		{
		public:

			std::vector<unsigned char> Press(const std::vector<unsigned char>& _pressBase)override;

			std::vector<unsigned char> Thaw(const std::vector<unsigned char>& _thawBase)override;

		private:



		};
	}
}

#endif
