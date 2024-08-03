#ifndef Ch_CPP_JsonNumber_h
#define Ch_CPP_JsonNumber_h

#include"ChJsonBaseType.h"

#include"../../BasePack/ChMath.h"
#include"../../BasePack/ChStr.h"


#ifndef CH_JSON_NUMBER_MATH_METHOD
#define CH_JSON_NUMBER_MATH_METHOD(_Operator,_MathValue)\
JsonNumber& operator _Operator (const JsonNumber& _val){\
	value _Operator _MathValue;\
	return *this;}
#endif

#ifndef CH_JSON_NUMBER_CONST_MATH_METHOD
#define CH_JSON_NUMBER_CONST_MATH_METHOD(_Operator)\
JsonNumber operator _Operator##(const JsonNumber& _val)const{\
	JsonNumber res = *this;\
	res _Operator##= _val;\
	return res;}
#endif

namespace ChCpp
{
	template<typename CharaType>
	class JsonNumber :public JsonBaseType<CharaType>
	{
	public://static Create Function//

#ifdef CRT
		template<typename BaseType>
		static ChPtr::Shared<JsonNumber> CreateObject(const BaseType& _value)
		{
			auto&& res = ChPtr::Make_S<JsonNumber>();
			*res = _value;
			return res;
		}
#endif

	public://Operator Functions//

		JsonNumber& operator = (const JsonNumber& _val)
		{
			if (this == &_val)return *this;
			value = _val.value;
			return *this;
		}

		CH_JSON_NUMBER_MATH_METHOD(+=, _val.value);
		CH_JSON_NUMBER_MATH_METHOD(-=, _val.value);
		CH_JSON_NUMBER_MATH_METHOD(*=, _val.value);
		CH_JSON_NUMBER_MATH_METHOD(/=, _val.value != 0.0l ? _val.value : 1.0l);

		JsonNumber& operator %= (const JsonNumber& _val)
		{
			value = ChMath::GetFMod(value, _val.value);
			return *this;
		}

		CH_JSON_NUMBER_CONST_MATH_METHOD(+);
		CH_JSON_NUMBER_CONST_MATH_METHOD(-);
		CH_JSON_NUMBER_CONST_MATH_METHOD(*);
		CH_JSON_NUMBER_CONST_MATH_METHOD(/);
		CH_JSON_NUMBER_CONST_MATH_METHOD(%);

	public://To BaseClass Operator Functions//

		template<typename BaseType>
		operator BaseType()const
		{
			return static_cast<BaseType>(value);
		}

		template<typename BaseType>
		JsonNumber& operator = (const BaseType& _base)
		{
			value = static_cast<const long double>(_base);
			return *this;
		}


	public://To String Operator Functions//

#ifdef CRT
		operator std::basic_string<CharaType>()const
		{
			return ToString();
		}
#endif

	public://Constructor Destructor//

		JsonNumber()
		{
			value = 0.0l;
		}

		JsonNumber(const JsonNumber& _val)
		{
			value = _val.value;
		}

		template<typename BaseType>
		JsonNumber(const BaseType& _val)
		{
			value = static_cast<long double>(_val);
		}

	public:

#ifdef CRT
		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override
		{
			if (!ChStd::IsBaseNumbers<CharaType>(_jsonText, ChStd::DECIMAL_NUMBUR<CharaType>()))return false;

			value = ChStr::GetNumFromText<long double, CharaType>(_jsonText);
			return true;
		}
#endif

	public:

#ifdef CRT
		std::basic_string<CharaType> GetRawData()const override
		{
			return ToString();
		}
#endif

	public:

#ifdef CRT
		std::basic_string<CharaType> ToString()const
		{
			std::basic_string<CharaType> tmpStr = ChStr::GetTextFromNum<CharaType>(value);
			unsigned long endPoint = tmpStr.find(ChStd::GetDotChara<CharaType>());
			for (unsigned long i = endPoint + 1; i < tmpStr.size(); i++)
			{
				if (tmpStr[i] == ChStd::GetZeroChara<CharaType>()[0])continue;
				endPoint = i + 1;
			}

			if (endPoint >= tmpStr.size())
			{
				return tmpStr;
			}

			return tmpStr.substr(0, endPoint);
		}
#endif

	private:

		long double value;
	};

}

#ifdef CRT
#ifdef Ch_CPP_JsonArray_h

template<typename CharaType>
template<typename BaseType>
void ChCpp::JsonArray<CharaType>::Add(const BaseType _value)
{
	if (_value == nullptr)return;
	values.push_back(JsonNumber<CharaType>::CreateObject(_value));
}

#endif
#endif

#endif