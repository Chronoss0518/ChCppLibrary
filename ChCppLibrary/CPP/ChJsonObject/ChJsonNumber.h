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
JsonNumber operator _Operator(const JsonNumber& _val)const{\
	JsonNumber res = *this;\
	res _Operator##= _val;\
	return res;}
#endif

#ifndef	CH_Json_Number_Create_Functions
#define	CH_Json_Number_Create_Functions(_type)\
static ChPtr::Shared<JsonNumber> CreateObject(const _type& _value){\
	auto&& res = ChPtr::Make_S<JsonNumber>();\
	*res = _value;\
	return res;}
#endif

#ifndef	CH_Json_Number_Constructor_Functions
#define	CH_Json_Number_Constructor_Functions(_type) JsonNumber(const _type & _val){value = static_cast<long double>(_val);}
#endif

#ifndef	CH_Json_Number_Operator_Functions
#define	CH_Json_Number_Operator_Functions(_type)\
operator _type()const{return static_cast<_type>(value);}\
\
JsonNumber& operator = (const _type & _base){\
	value = static_cast<const long double>(_base);\
	return *this;}
#endif


namespace ChCpp
{
	template<typename CharaType>
	class JsonNumber :public JsonBaseType<CharaType>
	{
	public://static Create Function//

		Ch_Json_BaseTypeMethods(CH_Json_Number_Create_Functions);

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

		Ch_Json_BaseTypeMethods(CH_Json_Number_Operator_Functions);

	public://To String Operator Functions//

		operator std::basic_string<CharaType>()const
		{
			return ToString();
		}

	public://Constructor Destructor//

		JsonNumber()
		{
			value = 0.0l;
		}

		JsonNumber(const JsonNumber& _val)
		{
			value = _val.value;
		}


		Ch_Json_BaseTypeMethods(CH_Json_Number_Constructor_Functions);

	public:

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

	public:

		std::basic_string<CharaType> GetRawData()const override
		{
			return ToString();
		}

	public:

		std::basic_string<CharaType> ToString()const;

	private:

		long double value;
	};

}

#endif