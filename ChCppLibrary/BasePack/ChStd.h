#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

//ChLibrary�̃x�[�X�ƂȂ�֐��A�ϐ��Q�̂܂Ƃ܂�//
namespace ChStd
{

	//X�t�@�C���ȂǑ����̃I�u�W�F�N�g�𗘗p����ۂɎ��ʎq�Ƃ��ė��p����B//
	using DataNo = unsigned short;

	//�ʏ��bool�^���1�`3Byte�y����������//
	//���݂ł�bool = 1Byte//
	//�r�b�g���Z�q�����p�ł��邽�߂�����͎c���Ă���//
	using Bool = unsigned char;

	//10�i��//
	static const std::vector<char> DECIMAL_NUMBUR() { return { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; };
	
	//16�i��//
	static const std::vector<char> HEXA_DECIMAL() { return  { '0', '1', '2' , '3', '4' , '5' , '6', '7' , '8', '9', 'A', 'B', 'C', 'D' , 'E', 'F' }; };

	//8�i��//
	static const std::vector<char> OCTAL() { return   { '0', '1', '2' , '3', '4' , '5' , '6', '7' }; };

	//2�i��//
	static const std::vector<char> BINARY_NUMBER() { return   { '0', '1'}; };

	//64�i��//
	static const std::vector<char> BASE_NUMBER_64() { return
		{ 'A', 'B', 'C', 'D' , 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a', 'b', 'c', 'd' , 'e', 'f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
		,'0', '1', '2' , '3', '4' , '5' , '6', '7' , '8', '9','+','/' };
	};

#ifdef _WIN32
	
	//Windows�Ŏg�p����鑊�΃p�X�E��΃p�X�̍ő啶����//
	static const unsigned short W_MAX_PATH_LEN = 258;

#elif _WIN64

	//Windows�Ŏg�p����鑊�΃p�X�E��΃p�X�̍ő啶����//
	static const unsigned short W_MAX_PATH_LEN = 258;

#endif

	///////////////////////////////////////////////////////////////////////////////////////
	//StanderdFunction
	///////////////////////////////////////////////////////////////////////////////////////

	const static unsigned char MAX_CHAR_BIT = 0x80;
	const static unsigned short MAX_SHORT_BIT = 0x8000;
	const static unsigned long MAX_LONG_BIT = 0x80000000;
	const static unsigned long long MAX_LLONG_BIT = 0x8000000000000000;

#ifdef _WIN64
	const static unsigned int W_MAX_INT_BIT = MAX_LONG_BIT;
#else
	const static unsigned int W_MAX_INT_BIT = MAX_SHORT_BIT;
#endif

	//EnumClass�����^�փL���X�g���邽�߂̃N���X//
	template<typename Enum>
	static inline auto EnumCast(Enum _enum)->typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}

	//�w�肵���A�h���X���l0�ŏ���������//
	template<class T>
	static inline void MZero(T* _val)
	{
		void* tmp = static_cast<void*>(_val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmp) + i) = 0;
		}
	}

	//_base�̏���_copy�փR�s�[����//
	template<class T>
	static inline void MCopy(T* _copy, const T* _base)
	{
		void* tmpCopy = static_cast<void*>(_copy);
		const void* tmpBase = static_cast<const void*>(_base);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmpCopy) + i) = *(static_cast<const char*>(tmpBase) + i);
		}
	}

	template<typename Type>
	static inline Type BinaryToNumWithLittleEndian(const std::vector<char>& _binary, unsigned long _filePos = 0)
	{

		Type Num = 0;

		if (_filePos + sizeof(Type) >= _binary.size())return Num;

		void* tmp = &Num;

		for (unsigned long i = 0; i < sizeof(Type); i++)
		{
			auto& test = reinterpret_cast<char*>(tmp)[i];

			test = (_binary[i + _filePos]);
		}

		return Num;

	}

	//10�i���̐��l������Ǝw�肵���z��ɂ���Đ������ꂽ�i���\�L�ŏo�͂����//
	static inline std::vector<char> TenToBaseNumber(long _decimal, const std::vector<char>& _baseNumber = HEXA_DECIMAL())
	{
		bool mFlg = false;
		long decimal = 0;

		if (_decimal > 0)
		{
			decimal = _decimal;
		}
		else
		{
			decimal = -_decimal;
			mFlg = true;

		}

		unsigned long size = _baseNumber.size();
		unsigned long base = decimal / size;

		std::vector<char> out;

		out.push_back(_baseNumber[decimal % size]);

		if (base == 0)
		{
			return out;
		}

		for (auto tmp : TenToBaseNumber(base, _baseNumber))
		{
			out.push_back(tmp);
		}

		if (mFlg)
		{
			out.push_back('-');
		}

		return out;

	}

	//�w�肵���i���̔z�������Ǝw�肵���z��ɂ���Đ������ꂽ�i���\�L�ŏo�͂����//
	static inline std::vector<char> ToBaseNumber(const std::vector<char>& _decimal, const std::vector<char>& _beforeBaseNumber = DECIMAL_NUMBUR(), const std::vector<char>& _afterBaseNumber = HEXA_DECIMAL())
	{

		long base = 0;

		return TenToBaseNumber(base,_afterBaseNumber);

	}

	template<typename Type>
	static inline Type BinaryToNumWithBigEndian(const std::vector<char>& _binary, unsigned long _filePos = 0)
	{

		Type Num = 0;

		if (_filePos + sizeof(Type) >= _binary.size())return Num;

		void* tmp = &Num;

		for (unsigned long i = sizeof(Type) - 1; i >= 0; i--)
		{
			auto& test = reinterpret_cast<char*>(tmp)[sizeof(Type) - i - 1];

			test = (_binary[i + _filePos]);

			if (i == 0)break;
		}

		return Num;

	}

	template<typename Type>
	static inline std::map<Type,unsigned long> CreateHuffmanTree(const std::vector<Type>& _binary)
	{
		std::map<Type, unsigned long>out;

		return out;
	}

}

#endif