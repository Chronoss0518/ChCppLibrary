#ifndef Ch_CPP_Cmp_Dic_h
#define Ch_CPP_Cmp_Dic_h

#include"ChBaseCompressor.h"

namespace ChCpp
{
	class BitBool;

	namespace Cmp
	{
		class Huffman :public BaseCompressor
		{
		public:



			std::vector<char> Press(const std::vector<char>& _pressBase)override;

			std::vector<char> Thaw(const std::vector<char>& _thawBase)override;

		private:

			void CreateHuffmanTree(std::map<char, ChPtr::Shared<BitBool>>& _tree,const std::vector<char>& _pressBase);

		};

	}
}

#endif
