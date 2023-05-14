#ifndef Ch_CPP_Cmp_Def_h
#define Ch_CPP_Cmp_Def_h

#include"../ChBaseCompressor.h"

namespace ChCpp
{
	class BitBool;

	namespace Cmp
	{
		union CMF
		{
			struct
			{
				char cinfo : 4;
				char cm : 4;
			};
			char val;
		};

		union FLG
		{
			struct
			{
				char flevel : 2;
				char fdict : 1;
				char fcheck : 5;
			};
			char val;
		};

		//zlib.Deflate//
		class Deflate :public BaseCompressor, public ChCp::Initializer
		{
		public:

			std::vector<unsigned char> Compress(const std::vector<unsigned char>& _compressBase)override;

			std::vector<unsigned char> Decompress(const std::vector<unsigned char>& _decompressBase)override;

		private:

			bool dictionaryFirstFlg = false;

			struct Header
			{
				CMF cmf;
				FLG flg;
			};

		};
	}
}

#endif
