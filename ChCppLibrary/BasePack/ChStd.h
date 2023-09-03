#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

//ChLibrary�̃x�[�X�ƂȂ�֐��A�ϐ��Q�̂܂Ƃ܂�//
namespace ChStd
{
	//10�i��//
	const std::vector<char> DECIMAL_NUMBUR();

	//16�i��//
	const std::vector<char> HEXA_DECIMAL();

	//8�i��//
	const std::vector<char> OCTAL();

	//2�i��//
	const std::vector<char> BINARY_NUMBER();

	//64�i��//
	const std::vector<char> BASE_NUMBER_64();

#ifdef WIN32
	
	//Windows�Ŏg�p����鑊�΃p�X�E��΃p�X�̍ő啶����//
	static constexpr unsigned short W_MAX_PATH_LEN = 258;

#else

	//Windows�Ŏg�p����鑊�΃p�X�E��΃p�X�̍ő啶����//
	static constexpr unsigned short W_MAX_PATH_LEN = 258;

#endif

	///////////////////////////////////////////////////////////////////////////////////////
	//StanderdFunction
	///////////////////////////////////////////////////////////////////////////////////////

	constexpr static unsigned char MAX_CHAR_BIT = 1 << 7;
	constexpr static unsigned short MAX_SHORT_BIT = 1 << 15;
	constexpr static unsigned long MAX_LONG_BIT = 1 << 31;
	constexpr static unsigned long long MAX_LLONG_BIT = 1 << 63;

#ifdef WIN32
	constexpr static unsigned int W_MAX_INT_BIT = MAX_SHORT_BIT;
#else
	constexpr static unsigned int W_MAX_INT_BIT = MAX_LONG_BIT;
#endif

	//EnumClass�����^�փL���X�g���邽�߂̃N���X//
	template<typename Enum>
	constexpr static inline auto EnumCast(const Enum _enum)->typename std::enable_if
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
	std::vector<char> DecimalNumberToBaseNumber(const long _decimal, const std::vector<char>& _baseNumber = HEXA_DECIMAL());

	//�w�肵���i���̔z��������10�i���̐��l���o�͂����//
	long BaseNumberToDecimalNumber(const std::vector<char>& _decimal, const std::vector<char>& _baseNumber = HEXA_DECIMAL());

	//�w�肵���i���̔z�������Ǝw�肵���z��ɂ���Đ������ꂽ�i���\�L�ŏo�͂����//
	std::vector<char> ToBaseNumber(const std::vector<char>& _baseNum, const std::vector<char>& _beforeBaseNumber = DECIMAL_NUMBUR(), const std::vector<char>& _afterBaseNumber = HEXA_DECIMAL());

	//�w�肵���V���̔z�������Ƃ��̔z��ɂ���Đ��l��u���ł��邩�̃e�X�g���s��//
	bool IsBaseNumbers(const std::vector<char>& _baseNum, const std::vector<char>& _beforeBaseNumber = DECIMAL_NUMBUR());

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