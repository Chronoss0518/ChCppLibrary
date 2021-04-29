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

#ifdef _WIN32
	
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
	const static unsigned int W_MAX_INT_BIT = 0x80000000;
#else
	const static unsigned int W_MAX_INT_BIT = 0x8000;
#endif

	//�J�n���Ɏg�p���A�����_���Ȓl���Z�b�g����//
	static inline void SetRand(const unsigned long _useNo) { srand(_useNo); }

	//SetRand�g�p��rand�֐�����l�����o��//
	static inline unsigned short GetRand(const unsigned short _useNumCount)
	{
		return rand() % _useNumCount;
	}

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

	//�w�肵���A�h���X���l0�ŏ���������//
	template<class T>
	static inline void MCopy(T* _copy, const T* _base)
	{
		void* tmpCopy = static_cast<void*>(_copy);
		const void* tmpBase = static_cast<const void*>(_base);

		for (unsigned long i = 0; i < sizeof(T); i++)
		{
			*(static_cast<char*>(tmpCopy) + i) = *(static_cast<char*>(tmpBase) + i);
		}
	}

}

#endif