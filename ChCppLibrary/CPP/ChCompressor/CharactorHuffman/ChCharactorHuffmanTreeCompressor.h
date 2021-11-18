#ifndef Ch_CPP_Cmp_Huf_h
#define Ch_CPP_Cmp_Huf_h

#include"../ChBaseCompressor.h"

namespace ChCpp
{
	class BitBool;

	namespace Cmp
	{
		//EasyHuffmanCompress//
		class CharactorHuffmanTree :public BaseCompressor,public ChCp::Initializer
		{
		public:

			inline void SetAnnotation(const unsigned char _dictionaryAnnotation) { dictionaryAnnotation = _dictionaryAnnotation; }

			inline void SetDictionaryFirstFlg(const ChStd::Bool _flg) { dictionaryFirstFlg = _flg; }

			std::vector<unsigned char> Press(const std::vector<unsigned char>& _pressBase)override;

			std::vector<unsigned char> Thaw(const std::vector<unsigned char>& _thawBase)override;

		private:

			unsigned char dictionaryAnnotation = 0;
			ChStd::Bool dictionaryFirstFlg = false;

		};
	}
}

#endif
