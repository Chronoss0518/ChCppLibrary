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

			inline void SetDictionaryFirstFlg(const bool _flg) { dictionaryFirstFlg = _flg; }

			inline void SethighToZeroFlgTrue() { highToZeroFlg = 0; }

			inline void SethighToZeroFlgFalse() { highToZeroFlg = 1; }

			std::vector<unsigned char> Compress(const std::vector<unsigned char>& _compressBase)override;

			std::vector<unsigned char> Decompress(const std::vector<unsigned char>& _decompressBase)override;

		private:

			struct TreeObject
			{
				unsigned long frequency = 0;
				unsigned char value = 0;

			};

			struct RootObject
			{
				unsigned long frequency = 0;

				std::vector<ChPtr::Shared<TreeObject>>objects;
			};

			struct FlgObject
			{
				unsigned long value = 0;

				unsigned char bitSize = 0;
			};

			union FirstFlgment
			{

				unsigned char value = 0;
				
				struct
				{
					unsigned char dictionaryFirstFlg : 1;
					unsigned char charaMaxByte : 3;
					unsigned char unUsedLastByte : 3;
				};
			};

			/*
			//Header First 3 Byte//
			ÅEFIrstFlgment
			ÅEDictionaryAnnotation
			ÅEAnnotationCountInDictionary
			*/

			void CreateDictionary(std::vector<unsigned char>& _out,unsigned char& _annotationInDictionary, BitBool& _nowByte, unsigned char& _nowCount,const std::map<unsigned char, FlgObject>& _fObject, const unsigned char _maxByteSize);

			void CreateMaps(std::map<unsigned char, FlgObject>& _maps,const std::vector<unsigned char>& _compressBase);

			void CreateRootObject(std::map<unsigned char, FlgObject>& _maps, const RootObject& _object,const FlgObject& _nowFlg = FlgObject());

			void SetTreeBranchs(std::map<unsigned char, FlgObject>& _maps, RootObject& _obj, const FlgObject& _nowFlg = FlgObject());

			bool ChangeByteTest(BitBool& _nowByte, unsigned char& _readByteCount, unsigned long& _readBytePos, std::vector<unsigned char>& _dictionaryByte, const bool _dictionaryFirstFlg);

			void LoadDictionary(std::map<unsigned char, FlgObject>& _dictionary,unsigned long& _startPos, unsigned long& _endPos,const std::vector<unsigned char>& _decompressBase,const FirstFlgment _fFlgs,const unsigned char _annotatino,const unsigned char _annotationCountInDictionary = 0);

			bool highToZeroFlg = true;
			unsigned char dictionaryAnnotation = 0;
			bool dictionaryFirstFlg = false;

		};
	}
}

#endif
