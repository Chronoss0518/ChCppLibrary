#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

namespace ChStr
{

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T>
	static inline void StrBinaryToNum(
		T& _setData
		, const std::string& _str
		, const size_t& _sPos = 0)
	{
		_setData = 0;
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			unsigned char Test = _str[_sPos + i];
			if (Test <= 0)continue;
			_setData += (T)(Test << 8 * ((sizeof(T) - 1) - i));
		}

	}

	//クラス名を取得する関数//
	template<class T = int>
	static inline std::string GetTypeName()
	{
		std::string tmpStr = typeid(T).name();


		size_t tmp = tmpStr.find(" ");
		if (tmp == std::string::npos)tmp = 0;
		else tmp += 1;

		return &tmpStr[tmp];
	}

	//文字の置き換え//
	static inline std::string StrReplase(
		const std::string& _base
		, const std::string _before
		, const std::string _after = ""
	)
	{
		if (_base.find(_before) == _base.npos)return _base;

		std::string out = "";

		size_t tmpPos = 0;
		size_t testPos = 0;

		while (true)
		{
			testPos = _base.find(_before, tmpPos);

			if (testPos == _base.npos)break;

			out += _base.substr(tmpPos, testPos - tmpPos);

			out += _after;

			tmpPos = testPos + _before.length();

		}

		return out;
	}

	static inline std::string RemoveToWhiteSpaceChars(const std::string& _str)
	{

		std::string out = "";

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] <= WhiteSpaceInterfaceChar)continue;
			if (_str[i] == DelCharNum)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring RemoveToWhiteSpaceChars(const std::wstring& _str)
	{

		std::wstring out = L"";

		const char WhiteSpaceInterfaceChar = 32;
		const char DelCharNum = 127;

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] < WhiteSpaceInterfaceChar)continue;
			if (_str[i] == DelCharNum)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::string RemoveToChars(const std::string& _str, const char _rempveChars)
	{

		std::string out = "";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] == _rempveChars)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring RemoveToChars(const std::wstring& _str, const wchar_t _rempveChars)
	{

		std::wstring out = L"";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] == _rempveChars)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::string RemoveToUnNums(const std::string& _str)
	{

		std::string out = "";

		const char StartNum = '0';
		const char EndNum = '9';

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			ChStd::Bool ConFlg = false;

			if (_str[i] < StartNum)ConFlg = true;
			if (_str[i] > EndNum)ConFlg = true;

			if (_str[i] == '.')ConFlg = false;
			if (_str[i] == '-')ConFlg = false;

			if (ConFlg)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring RemoveToUnNums(const std::wstring& _str)
	{

		std::wstring out = L"";

		const wchar_t StartNum = L'0';
		const wchar_t EndNum = L'9';

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			ChStd::Bool conFlg = false;

			if (_str[i] < StartNum)conFlg = true;
			if (_str[i] > EndNum)conFlg = true;

			if (_str[i] == L'.')conFlg = false;
			if (_str[i] == L'-')conFlg = false;

			if (conFlg)continue;
			out = out + _str[i];

		}
		return out;
	}

	static inline std::string GetCharsToRangeCode(
		const std::string& _str
		, const char _min
		, const char _max)
	{

		std::string out = "";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] > _max || _str[i] < _min)continue;

			out = out + _str[i];

		}

		return out;
	}

	static inline std::wstring GetCharsToRangeCode(
		const std::wstring& _str
		, const wchar_t _min
		, const wchar_t _max)
	{

		std::wstring out = L"";

		for (unsigned long i = 0; i < _str.length(); i++)
		{
			if (_str[i] > _max || _str[i] < _min)continue;

			out = out + _str[i];

		}
		return out;
	}

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::string& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		long long tmp = std::atoll(useText.c_str());

		return static_cast<BaseType>(tmp);

	}

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::string& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		double tmp = std::atof(useText.c_str());

		return static_cast<BaseType>(tmp);
	}

	template<typename BaseType>
	inline auto GetIntegialFromText(
		const std::wstring& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::string::npos)
		->typename std::enable_if<
		std::is_integral<BaseType>::value
		&& !std::is_same<bool, BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::wstring useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		long long tmp = std::atoll(useText.c_str());

		return static_cast<BaseType>(tmp);
	}

	template<typename BaseType>
	inline auto GetFloatingFromText(
		const std::wstring& _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = std::wstring::npos)
		->typename std::enable_if<
		std::is_floating_point<BaseType>::value, BaseType>::type

	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::wstring useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		double tmp = std::atof(useText.c_str());

		return static_cast<BaseType>(tmp);

	}


	using convert_t = std::codecvt_utf8<wchar_t>;

	static std::wstring_convert<convert_t, wchar_t> strconverter;

	inline std::wstring ToWString(const std::string _str)
	{
		return strconverter.from_bytes(_str);
	}

	inline std::string ToString(const std::wstring _str)
	{
		return strconverter.to_bytes(_str);
	}

}


#endif