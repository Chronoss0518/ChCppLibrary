#ifndef Ch_CRT_String
#define Ch_CRT_String

#include"../ChCRTBase.h"

#ifdef CRT
#include<string>
#endif

#ifndef Ch_CRT_String_Operators
#define Ch_CRT_String_Operators(_TargetType)\
StringPack& operator =(const _TargetType _val);\
StringPack operator +(const _TargetType _val)const;\
StringPack& operator +=(const _TargetType _val);\
bool operator ==(const _TargetType _str)const;\
bool operator !=(const _TargetType _str)const;\
bool operator <(const _TargetType _str)const;\
bool operator <=(const _TargetType _str)const;\
bool operator >(const _TargetType _str)const;\
bool operator >=(const _TargetType _str)const;
#endif

namespace ChCRT
{
	template<typename CharaType>
	class StringPack final
	{
		struct StringPackCRT
		{
#ifdef CRT
			std::basic_string<CharaType>pack = InitString();
#endif
		};

	public:


#ifdef CRT
		inline StringPack& operator =(const std::basic_string<CharaType>& _val) { if (reinterpret_cast<size_t>(&value->pack) != reinterpret_cast<size_t>(&_val))value->pack = _val; return *this; }
#endif

		Ch_CRT_String_Operators(CharaType*);
		Ch_CRT_String_Operators(StringPack<CharaType>&);

		StringPack& operator =(const CharaType& _val);
		StringPack operator +(const CharaType& _val)const;
		StringPack& operator +=(const CharaType& _val);
		
		CharaType& operator[](const size_t _num);
		const CharaType& operator [](const size_t _num) const;

		operator const CharaType* ()const;

#ifdef CRT

		bool operator ==(const std::basic_string<CharaType>& _str)const { return value->pack == _str; }

		bool operator !=(const std::basic_string<CharaType>& _str)const { return value->pack != _str; }

		bool operator <(const std::basic_string<CharaType>& _str)const { return value->pack < _str; }

		bool operator <=(const std::basic_string<CharaType>& _str)const { return value->pack <= _str; }

		bool operator >(const std::basic_string<CharaType>& _str)const { return value->pack > _str; }

		bool operator >=(const std::basic_string<CharaType>& _str)const { return value->pack >= _str; }

#endif

	public:

		Ch_CRT_ConstructorDestructor_Functions(StringPack, std::basic_string<CharaType>);

		StringPack(const CharaType& _str);

		StringPack(const CharaType* _str);

		StringPack(const StringPack& _str);

		StringPack(StringPack&& _str);

		StringPack();

		~StringPack();

	private:

		static const CharaType* InitString();

	public:

		void SetString(const CharaType* _str);

	public:

		size_t GetSize()const;

		size_t GetLength()const;

		size_t GetFindPosition(const CharaType* _findStr,const size_t _start = 0)const;

		size_t GetFindPositionFromEnd(const CharaType* _findStr, const size_t _start = 0)const;

		StringPack GetSubStr(const size_t _pos, const size_t _n = GetNPos())const;

		const CharaType* GetString()const;

#ifdef CRT
		std::basic_string<CharaType>& GetPackString() { return value->pack; }
#endif

	public:

		static size_t GetNPos();

	public:

		bool IsString(const CharaType* _str);

	public:

		void Pop();

	private:

		StringPackCRT* value = nullptr;

	};

	using String = StringPack<char>;
	using WString = StringPack<wchar_t>;
#ifdef CPP20
	using U8String = StringPack<char8_t>;
#endif
	using U16String = StringPack<char16_t>;
	using U32String = StringPack<char32_t>;


	//当分の間ToStringとToNumはこちらを利用する//
	template<typename _BaseType>
	String ToString(const _BaseType _type);

	//当分の間ToStringとToNumはこちらを利用する//
	template<typename _BaseType>
	WString ToWString(const _BaseType _type);

	template<typename _CharaType,typename _BaseType>
	StringPack<_CharaType> ToStringPack(const _BaseType _type);


	//当分の間ToStringとToNumはこちらを利用する//
	template<typename _BaseType>
	_BaseType ToNum(const String& _str);

	//当分の間ToStringとToNumはこちらを利用する//
	template<typename _BaseType>
	_BaseType ToNum(const WString& _str);

	template<typename _CharaType, typename _BaseType>
	_BaseType ToNumPack(const StringPack<_CharaType>& _type);

}

#endif