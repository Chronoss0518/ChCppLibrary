#ifndef Ch_CPP_Cmp_Base_h
#define Ch_CPP_Cmp_Base_h

namespace ChCpp
{
	namespace Cmp
	{
		unsigned long CreateAdler32(const std::vector<unsigned char>& _base);


		 class BaseCompressor
		{
		public:

			///////////////////////////////////////////////////////////////////////////////////
			
			//���k�֐�//
			virtual std::vector<unsigned char> Compress(const std::vector<unsigned char>& _compressBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

			//�𓀊֐�//
			virtual std::vector<unsigned char> Decompress(const std::vector<unsigned char>& _decompressBase) = 0;

			///////////////////////////////////////////////////////////////////////////////////

		};

	}
}

#endif
