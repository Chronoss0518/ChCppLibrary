#define CRT

#include"ChStringPack.h"

using namespace ChCRT;

//templateÇÃñæé¶ìIêÈåæ//

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

#define Operators_Functions_Declare(_type,_modifier)\
template StringPack<##_type##>& StringPack<##_type##>::operator =(const _type##_modifier _val);\
template StringPack<##_type##> StringPack<##_type##>::operator +(const _type##_modifier _val)const;\
template StringPack<##_type##>& StringPack<##_type##>::operator +=(const _type##_modifier _val);\
template bool StringPack<##_type##>::operator ==(const _type##_modifier _str)const;\
template bool StringPack<##_type##>::operator !=(const _type##_modifier _str)const;\
template bool StringPack<##_type##>::operator <(const _type##_modifier _str)const;\
template bool StringPack<##_type##>::operator <=(const _type##_modifier _str)const;\
template bool StringPack<##_type##>::operator >(const _type##_modifier _str)const;\
template bool StringPack<##_type##>::operator >=(const _type##_modifier _str)const;\

#define EXPLICIT_DECLARATION(_type)\
template _type##& StringPack<##_type##>::operator[](const size_t _num);\
template const _type##& StringPack<##_type##>::operator [](const size_t _num) const;\
template StringPack<##_type##>& StringPack<##_type##>::operator =(const _type##& _str); \
template StringPack<##_type##> StringPack<##_type##>::operator +(const _type##& _str)const; \
template StringPack<##_type##>& StringPack<##_type##>::operator +=(const _type##& _str); \
Operators_Functions_Declare(_type,*);\
template StringPack<##_type##>& StringPack<##_type##>::operator =(const StringPack<##_type##>& _str);\
template StringPack<##_type##> StringPack<##_type##>::operator +(const StringPack<##_type##>& _str)const;\
template StringPack<##_type##>& StringPack<##_type##>::operator +=(const StringPack<##_type##>& _str);\
template bool StringPack<##_type##>::operator ==(const StringPack<##_type##>& _str)const;\
template bool StringPack<##_type##>::operator !=(const StringPack<##_type##>& _str)const;\
template bool StringPack<##_type##>::operator <(const StringPack<##_type##>& _str)const;\
template bool StringPack<##_type##>::operator <=(const StringPack<##_type##>& _str)const;\
template bool StringPack<##_type##>::operator >(const StringPack<##_type##>& _str)const;\
template bool StringPack<##_type##>::operator >=(const StringPack<##_type##>& _str)const;\
template StringPack<##_type##>::StringPack(const _type##& _str);\
template StringPack<##_type##>::StringPack(const _type##* _str);\
template StringPack<##_type##>::StringPack(const StringPack<##_type##>& _str);\
template StringPack<##_type##>::StringPack(StringPack<##_type##>&& _str);\
template StringPack<##_type##>::StringPack();\
template StringPack<##_type##>::~StringPack();\
template void StringPack<##_type##>::SetString(const _type##* _str);\
template size_t StringPack<##_type##>::GetSize()const;\
template size_t StringPack<##_type##>::GetLength()const;\
template size_t StringPack<##_type##>::GetFindPosition(const _type##* _findStr)const;\
template size_t StringPack<##_type##>::GetFindPositionFromEnd(const _type##* _findStr)const;\
template const _type##* StringPack<##_type##>::GetString();\
template StringPack<##_type##> StringPack<##_type##>::GetSubStr(const size_t _pos, const size_t _n)const;\
template size_t StringPack<##_type##>::GetNPos();\
template bool StringPack<##_type##>::IsString(const _type##* _str);

template<> const char* StringPack<char>::InitString() { return "\0"; }
template<> const wchar_t* StringPack<wchar_t>::InitString() { return L"\0"; }
template<> const char8_t* StringPack<char8_t>::InitString() { return u8"\0"; }
template<> const char16_t* StringPack<char16_t>::InitString() { return u"\0"; }
template<> const char32_t* StringPack<char32_t>::InitString() { return U"\0"; }

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
size_t StringPack<CharaType>::GetFindPosition(const CharaType* _findStr)const { return value->pack.find(_findStr); }

template<typename CharaType>
size_t StringPack<CharaType>::GetFindPositionFromEnd(const CharaType* _findStr)const { return value->pack.rfind(_findStr); }

template<typename CharaType>
const CharaType* StringPack<CharaType>::GetString() { return value->pack.c_str(); }

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

template ChCRT::StringPack<char>;
template ChCRT::StringPack<wchar_t>;
template ChCRT::StringPack<char8_t>;
template ChCRT::StringPack<char16_t>;
template ChCRT::StringPack<char32_t>;