#include"ChModelControllerBase.h"

template<> std::basic_string<char> ChCpp::GetConvertText(const std::string& _str)
{
	return _str;
}

template<> std::basic_string<wchar_t> ChCpp::GetConvertText(const std::string& _str)
{
	return ChStr::GetUTF16FromShiftJis(_str);
}

template<> std::basic_string<char> ChCpp::GetConvertText(const std::wstring& _str)
{
	return ChStr::GetShiftJisFromUTF16(_str);
}

template<> std::basic_string<wchar_t> ChCpp::GetConvertText(const std::wstring& _str)
{
	return _str;
}
