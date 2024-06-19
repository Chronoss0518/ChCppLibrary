#ifndef Ch_CPP_Str_h
#define Ch_CPP_Str_h

#include"ChPtr.h"
#include"ChAllocArray.h"


namespace ChStr
{

	template<typename CharaType = char>
	class BaseString
	{
	public:

		BaseString& operator=(const BaseString& _str) { Set(_str); return *this; }

		BaseString& operator += (const BaseString& _str) { Add(_str); return *this; }

		BaseString operator + (const BaseString& _str)const 
		{
			BaseString res = *this;
			res.Add(_str);
			return res;
		}

		BaseString& operator += (const CharaType _str) { Add(&_str); return *this; }

		BaseString operator + (const CharaType _str)const 
		{
			BaseString res = *this;
			res.Add(_str);
			return res;
		}

		CharaType operator[](unsigned long _num) 
		{
			if (_num >= GetLength())return 0;
			return str[_num];
		}

		const CharaType operator[](unsigned long _num)const
		{
			if (_num >= GetLength())return 0;
			return str[_num];
		}

		operator const CharaType* () const { return GetCStr(); }

	public:

		BaseString() { Set(static_cast<CharaType>(0)); }

		BaseString(const CharaType* _char) { Set(_char); }

		BaseString(const CharaType _char) { Set(&_char); }

		BaseString(const BaseString& _str) { Set(_str); }

		~BaseString() { Release(); }

	private:

		void Release();

	public:

		void Set(const CharaType* _char);

		void Set(const BaseString& _str)
		{
			Set(_str.str);
		}

		inline void Set(const CharaType _char) { Set(&_char); }

		void Add(const BaseString& _str);

		inline void Add(const CharaType _char) { Add(&_char); }

	public:

		unsigned long GetLength()const;

		inline const CharaType* const GetCStr()const { return str; }

	public:

		long Find(
			const BaseString& _str,
			unsigned long _start = 0)
		{
			if (GetLength() <= 0)return -1;
			if (_str.GetLength() <= 0)return -1;
			if (GetLength() - _start < _str.GetLength())return -1;

			bool findFlg = true;

			for (unsigned long i = _start; i < GetLength() - _str.GetLength() + 1; i++)
			{
				findFlg = true;
				for (unsigned long j = 0; j < _str.GetLength(); j++)
				{
					if (_str.str[j] == str[i + j])continue;
					findFlg = false;

				}
				if (findFlg)
					return i;
			}

			return -1;
		}

		long Find(
			CharaType _char,
			unsigned long _start = 0) { Find(&_char, _start); }

		long FindFromLast(
			const BaseString& _str,
			unsigned long _start = 0)
		{
			if (GetLength() <= 0)return -1;
			if (_str.GetLength() <= 0)return -1;
			if (_start >= GetLength())_start = GetLength();
			if (GetLength() < _str.GetLength())return -1;

			bool findFlg = true;

			for (unsigned long i = _start; i < GetLength(); i++)
			{
				findFlg = true;
				for (unsigned long j = 0; j < _str.GetLength(); j++)
				{
					if (_str.str[j] == str[GetLength() - i - j])continue;
					findFlg = false;

				}
				if (!findFlg)continue;
				return GetLength() - i - _start;
			}

			return -1;
		}

		unsigned long FindFromLast(
			CharaType _char,
			unsigned long _start = 0)
		{
			FindFromLast(&_char, _start);
		}

	public:

		void Replace(
			const BaseString _before,
			const BaseString _after,
			unsigned long _start = 0);

	public:

		BaseString SubStr(unsigned long _start, unsigned long _count)
		{
			if (GetLength() <= 0)return "";
			if (_start >= GetLength())return "";
			if (static_cast<unsigned long long>(_start) + static_cast<unsigned long long>(_count) >= static_cast<unsigned long long>(GetLength()))return &str[_start];

			BaseString res = &str[_start];
			res.ReSize(_count);

			return res;
		}

	public:

		ChArray::AllocArray<BaseString> Split(const CharaType _str)
		{
			return Split(&_str);
		}

		ChArray::AllocArray<BaseString> Split(const BaseString _str);


	public:

		void ReSize(unsigned long _value);

	private:

		CharaType* str = nullptr;
	};

	//文字列をバイナリデータにして//
	//整数型に変換する//
	template<typename T, typename CharType>
	static inline void StrBinaryToNum(
		T& _setData
		, const BaseString<CharType>& _str
		, const size_t& _sPos = 0)
	{
		
		_setData = 0;
		for (unsigned char i = 0; i < sizeof(T); i++)
		{
			if (_str[_sPos + i] == 0)break;

			unsigned char Test = _str[_sPos + i];
			if (Test <= 0)continue;
			_setData += (T)(Test << 8 * ((sizeof(T) - 1) - i));
		}

	}

	//クラス名を取得する関数//
	template<typename CharaType, class T>
	static inline BaseString<CharaType> GetTypeName();

	template<typename CharType>
	//文字の置き換え//
	BaseString<CharType> StrReplase(
		const BaseString<CharType>& _base,
		const BaseString<CharType>& _before,
		const BaseString<CharType>& _after = "");

	//空文字を取り除く//
	template<typename CharType>
	BaseString<CharType> RemoveToWhiteSpaceChars(const BaseString<CharType>& _str);

	//指定した文字を取り除く//
	template<typename CharType>
	BaseString<CharType> RemoveToChars(const BaseString<CharType> _str, const BaseString<CharType> _rempveChars);

	//数値に変換可能な文字以外の文字を取り除く//
	template<typename CharType>
	BaseString<CharType> RemoveToUnNums(const BaseString<CharType> _str);

	//対象の文字で区切り配列にする//
	template<typename CharType>
	ChArray::AllocArray<BaseString<CharType>> Split(const CharType* _str, const CharType* _splitChar);

	//指定されたコード値の範囲の文字のみを返す//
	template<typename CharType>
	BaseString<CharType> GetCharsToRangeCode(
		const BaseString<CharType> _str,
		const CharType _min,
		const CharType _max);

	template<typename BaseType, typename CharType>
	inline BaseType GetIntegialFromText(
		const BaseString<CharType> _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = -1)
	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		if (useText.empty())return static_cast<BaseType>(0);

		long long tmp = std::stoll(useText.c_str());

		return static_cast<BaseType>(tmp);
	}

	template<typename BaseType, typename CharType>
	inline BaseType GetFloatingFromText(
		const CharType* _text
		, const size_t& _startPos = 0
		, const size_t& _endPos = -1)
	{
		size_t endPos = _endPos;

		if (_text.size() <= endPos)
		{
			endPos = _text.size();
		}

		std::string useText = _text.substr(_startPos, endPos - _startPos);

		useText = RemoveToUnNums(useText);

		if (useText.empty())return static_cast<BaseType>(0.0);

		double tmp = std::stof(useText.c_str());

		return static_cast<BaseType>(tmp);
	}


}


#endif