#ifndef Ch_CPP_Std_h
#define Ch_CPP_Std_h

//ChLibraryのベースとなる関数、変数群のまとまり//
namespace ChStd
{
	//10進数//
	const std::vector<char> DECIMAL_NUMBUR();

	//16進数//
	const std::vector<char> HEXA_DECIMAL();

	//8進数//
	const std::vector<char> OCTAL();

	//2進数//
	const std::vector<char> BINARY_NUMBER();

	//64進数//
	const std::vector<char> BASE_NUMBER_64();

#ifdef WIN32
	
	//Windowsで使用される相対パス・絶対パスの最大文字数//
	static constexpr unsigned short W_MAX_PATH_LEN = 258;

#else

	//Windowsで使用される相対パス・絶対パスの最大文字数//
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

	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	constexpr static inline auto EnumCast(const Enum _enum)->typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}

	//指定したアドレス先を値0で初期化する//
	template<class T>
	static inline void MZero(T* _val)
	{
		void* tmp = static_cast<void*>(_val);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmp) + i) = 0;
		}
	}

	//_baseの情報を_copyへコピーする//
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

	//10進数の数値を入れると指定した配列によって生成された進数表記で出力される//
	std::vector<char> DecimalNumberToBaseNumber(const long _decimal, const std::vector<char>& _baseNumber = HEXA_DECIMAL());

	//指定した進数の配列を入れると10進数の数値が出力される//
	long BaseNumberToDecimalNumber(const std::vector<char>& _decimal, const std::vector<char>& _baseNumber = HEXA_DECIMAL());

	//指定した進数の配列を入れると指定した配列によって生成された進数表記で出力される//
	std::vector<char> ToBaseNumber(const std::vector<char>& _baseNum, const std::vector<char>& _beforeBaseNumber = DECIMAL_NUMBUR(), const std::vector<char>& _afterBaseNumber = HEXA_DECIMAL());

	//指定した新数の配列を入れるとその配列によって数値を置換できるかのテストを行う//
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