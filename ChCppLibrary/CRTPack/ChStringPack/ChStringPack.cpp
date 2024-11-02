#define CRT

#include"ChStringPack.h"

#include<cstdlib>
#include<wchar.h>

using namespace ChCRT;

#define Operators_Functions(_TargetType)\
template<typename CharaType> StringPack<CharaType>& StringPack<CharaType>::operator =(const _TargetType _val){ value->pack = _val; return *this; } \
template<typename CharaType> StringPack<CharaType> StringPack<CharaType>::operator +(const _TargetType _val)const{ StringPack<CharaType>res = *this;res += _val; return res; } \
template<typename CharaType> StringPack<CharaType>& StringPack<CharaType>::operator +=(const _TargetType _val){ value->pack += _val; return *this; } \
template<typename CharaType> bool StringPack<CharaType>::operator ==(const _TargetType _str)const { return value->pack == _str; }\
template<typename CharaType> bool StringPack<CharaType>::operator !=(const _TargetType _str)const { return value->pack != _str; }\
template<typename CharaType> bool StringPack<CharaType>::operator <(const _TargetType _str)const { return value->pack < _str; }\
template<typename CharaType> bool StringPack<CharaType>::operator <=(const _TargetType _str)const { return value->pack <= _str; }\
template<typename CharaType> bool StringPack<CharaType>::operator >(const _TargetType _str)const { return value->pack > _str; }\
template<typename CharaType> bool StringPack<CharaType>::operator >=(const _TargetType _str)const { return value->pack >= _str; }\

template<typename CharaType>
CharaType& StringPack<CharaType>::operator[](const size_t _num) { return value->pack[_num]; }

template<typename CharaType>
const CharaType& StringPack<CharaType>::operator [](const size_t _num) const{ return value->pack[_num]; }

template<typename CharaType>
StringPack<CharaType>& StringPack<CharaType>::operator =(const CharaType& _val) { value->pack = _val; return *this; }

template<typename CharaType>
StringPack<CharaType> StringPack<CharaType>::operator +(const CharaType& _val)const { StringPack<CharaType>res = *this; res += _val; return res; }

template<typename CharaType>
StringPack<CharaType>& StringPack<CharaType>::operator +=(const CharaType& _val) { value->pack += _val; return *this; }

Operators_Functions(CharaType*);

template<typename CharaType>
StringPack<CharaType>::operator const CharaType* ()const { return value->pack.c_str(); }

template<typename CharaType>
StringPack<CharaType>& StringPack<CharaType>::operator =(const StringPack<CharaType>& _val) { value->pack = _val.value->pack; return *this; }

template<typename CharaType>
StringPack<CharaType> StringPack<CharaType>::operator +(const StringPack<CharaType>& _val)const { StringPack<CharaType>res = *this; res += _val.value->pack; return res; }

template<typename CharaType>
StringPack<CharaType>& StringPack<CharaType>::operator +=(const StringPack<CharaType>& _val) { value->pack += _val.value->pack; return *this; }


template<typename CharaType>
bool StringPack<CharaType>::operator ==(const StringPack<CharaType>& _str)const { return value->pack == _str.value->pack; }

template<typename CharaType>
bool StringPack<CharaType>::operator !=(const StringPack<CharaType>& _str)const { return value->pack != _str.value->pack; }

template<typename CharaType>
bool StringPack<CharaType>::operator <(const StringPack<CharaType>& _str)const { return value->pack < _str.value->pack; }

template<typename CharaType>
bool StringPack<CharaType>::operator <=(const StringPack<CharaType>& _str)const { return value->pack <= _str.value->pack; }

template<typename CharaType>
bool StringPack<CharaType>::operator >(const StringPack<CharaType>& _str)const { return value->pack > _str.value->pack; }

template<typename CharaType>
bool StringPack<CharaType>::operator >=(const StringPack<CharaType>& _str)const { return value->pack >= _str.value->pack; }

template<typename CharaType>
StringPack<CharaType>::StringPack(const CharaType& _str) 
{ 
	value = new StringPackCRT();
	SetString(&_str);
}

template<typename CharaType>
StringPack<CharaType>::StringPack(const CharaType* _str)
{
	value = new StringPackCRT();
	SetString(_str);
}

template<typename CharaType>
StringPack<CharaType>::StringPack(const StringPack<CharaType>& _str)
{
	value = new StringPackCRT();
	value->pack = _str.value->pack;
}

template<typename CharaType>
StringPack<CharaType>::StringPack(StringPack<CharaType>&& _str)
{
	value = new StringPackCRT();
	value->pack = _str.value->pack;
}

template<typename CharaType>
StringPack<CharaType>::StringPack() { value = new StringPackCRT(); }

template<typename CharaType>
StringPack<CharaType>::~StringPack() { delete value; }

template<typename CharaType>
void StringPack<CharaType>::SetString(const CharaType* _str) { value->pack = _str; }

template<typename CharaType>
size_t StringPack<CharaType>::GetSize()const { return value->pack.size(); }

template<typename CharaType>
size_t StringPack<CharaType>::GetLength()const { return value->pack.length(); }

template<typename CharaType>
size_t StringPack<CharaType>::GetFindPosition(const CharaType* _findStr, const size_t _start)const { return value->pack.find(_findStr, _start); }

template<typename CharaType>
size_t StringPack<CharaType>::GetFindPositionFromEnd(const CharaType* _findStr, const size_t _start)const { return value->pack.rfind(_findStr, _start); }

template<typename CharaType>
const CharaType* StringPack<CharaType>::GetString()const { return value->pack.c_str(); }

template<typename CharaType>
StringPack<CharaType> StringPack<CharaType>::GetSubStr(const size_t _pos, const size_t _n)const
{
	StringPack<CharaType> res = value->pack.substr(_pos, _n);
	return res;
}

template<typename CharaType>
size_t StringPack<CharaType>::GetNPos() { return std::basic_string<CharaType>::npos; }

template<typename CharaType>
bool StringPack<CharaType>::IsString(const CharaType* _str) { return value->pack == _str; }

template<typename CharaType>
void StringPack<CharaType>::Pop() { return value->pack.pop_back(); }

template<typename _BaseType>
String ChCRT::ToString(const _BaseType _type) { return std::to_string(_type); }

template<typename _BaseType>
WString ChCRT::ToWString(const _BaseType _type) { return std::to_wstring(_type); }


//templateÇÃñæé¶ìIêÈåæ//

#include"../../BasePack/ChStd.h"


#define EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(_BaseType,_EndMethodName)\
template<> _BaseType ChCRT::ToNum(const String& _str) { return static_cast<##_BaseType##>(ato##_EndMethodName##(_str.GetString())); }\
template<> _BaseType ChCRT::ToNum(const WString& _str) { return static_cast<##_BaseType##>(_wto##_EndMethodName##(_str.GetString())); }\

#define EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(_BaseType)\
template String ChCRT::ToString(const _BaseType _type);\
template WString ChCRT::ToWString(const _BaseType _type)

#define EXPLICIT_DECLARATION_PACK_FUNCTIONS(_BaseType)\
template<> StringPack<char> ChCRT::ToStringPack(const _BaseType _type) { return ChCRT::ToString<_BaseType>(_type); }\
template<> StringPack<wchar_t> ChCRT::ToStringPack(const _BaseType _type) { return ChCRT::ToWString<_BaseType>(_type); }\
template<> StringPack<char8_t> ChCRT::ToStringPack(const _BaseType _type) { return u8""; }\
template<> StringPack<char16_t> ChCRT::ToStringPack(const _BaseType _type) { return u""; }\
template<> StringPack<char32_t> ChCRT::ToStringPack(const _BaseType _type) { return U""; }\
template<> _BaseType ChCRT::ToNumPack(const StringPack<char>& _str) { return ChCRT::ToNum<_BaseType>(_str); }\
template<> _BaseType ChCRT::ToNumPack(const StringPack<wchar_t>& _str) { return ChCRT::ToNum<_BaseType>(_str); }\
template<> _BaseType ChCRT::ToNumPack(const StringPack<char8_t>& _str) { return static_cast<_BaseType>(0); }\
template<> _BaseType ChCRT::ToNumPack(const StringPack<char16_t>& _str) { return static_cast<_BaseType>(0); }\
template<> _BaseType ChCRT::ToNumPack(const StringPack<char32_t>& _str) { return static_cast<_BaseType>(0); }


EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(char, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(unsigned char, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(short, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(unsigned short, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(int, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(unsigned int, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(long, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(unsigned long, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(long long, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(unsigned long long, ll);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(float, f);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(double, f);
EXPLICIT_DECLARATION_TO_NUM_FUNCTIONS(long double, f);


EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(char);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(unsigned char);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(short);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(unsigned short);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(int);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(unsigned int);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(long);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(unsigned long);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(long long);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(unsigned long long);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(float);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(double);
EXPLICIT_DECLARATION_TO_STRING_FUNCTIONS(long double);

CH_BASE_TYPE_EXPLICIT_DECLARATION(EXPLICIT_DECLARATION_PACK_FUNCTIONS);

template<> const char* StringPack<char>::InitString() { return "\0"; }
template<> const wchar_t* StringPack<wchar_t>::InitString() { return L"\0"; }
template<> const char8_t* StringPack<char8_t>::InitString() { return u8"\0"; }
template<> const char16_t* StringPack<char16_t>::InitString() { return u"\0"; }
template<> const char32_t* StringPack<char32_t>::InitString() { return U"\0"; }

template ChCRT::StringPack<char>;
template ChCRT::StringPack<wchar_t>;
template ChCRT::StringPack<char8_t>;
template ChCRT::StringPack<char16_t>;
template ChCRT::StringPack<char32_t>;