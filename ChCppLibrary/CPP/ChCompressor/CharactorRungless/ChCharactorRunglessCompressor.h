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

			std::vector<unsigned char> Compress(const std::vector<unsigned char>& _compressBase)override;

			std::vector<unsigned char> Decompress(const std::vector<unsigned char>& _decompressBase)override;


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
