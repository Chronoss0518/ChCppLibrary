#ifndef Ch_CPP_BStd_CRT_h
#define Ch_CPP_BStd_CRT_h

#include"ChStd.h"

#include<iostream>

namespace ChStd
{
	//EnumClassを基底型へキャストするためのクラス//
	template<typename Enum>
	constexpr static inline auto EnumCast(const Enum _enum) -> typename std::enable_if
		<std::is_enum<Enum>::value, typename std::underlying_type< Enum >::type>::type
	{
		return static_cast<typename std::underlying_type<Enum>::type>(_enum);
	}
}

#endif