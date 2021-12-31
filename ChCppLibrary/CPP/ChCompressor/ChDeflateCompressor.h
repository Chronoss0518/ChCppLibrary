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

			std::vector<unsigned char> Compress(const std::vector<unsigned char>& _compressBase)override;

			std::vector<unsigned char> Decompress(const std::vector<unsigned char>& _decompressBase)override;

		private:



		};
	}
}

#endif
