#ifndef Ch_CPP_JsonString_h
#define Ch_CPP_JsonString_h

#include"ChJsonBaseType.h"

#include"../../BasePack/ChStr.h"

#ifndef	CH_Json_String_Operator_Functions
#define	CH_Json_String_Operator_Functions(_type)\
JsonString& operator =(const _type & _value){\
	value = ChStr::GetTextFromNum<CharaType>(_value);\
	return *this;}
#endif

#ifndef	CH_Json_String_Constructor_Functions
#define	CH_Json_String_Constructor_Functions(_type)\
JsonString(const _type & _value){\
	*this = ChStr::GetTextFromNum<CharaType>(_value);}
#endif

namespace ChCpp
{
	namespace Json
	{
		//"b"//
		CH_NUMBER_FUNCTION_BASE(Get_b_Chara);

		//"f"//
		CH_NUMBER_FUNCTION_BASE(Get_f_Chara);

		//"n"//
		CH_NUMBER_FUNCTION_BASE(Get_n_Chara);
		
		//"r"//
		CH_NUMBER_FUNCTION_BASE(Get_r_Chara);
		
		//"t"//
		CH_NUMBER_FUNCTION_BASE(Get_t_Chara);
	}

	template<typename CharaType>
	class JsonString :public JsonBaseType<CharaType>
	{
	public://static Create Function//

		static ChPtr::Shared<JsonString> CreateObject(const std::basic_string<CharaType>& _text)
		{
			auto&& res = ChPtr::Make_S<JsonString>();
			*res = _text;
			return res;
		}
	public://Operator Functions//

		JsonString& operator =(const JsonString& _value)
		{
			if (this == &_value)return *this;
			value = _value.value;
			return *this;
		}

		JsonString& operator +=(const JsonString& _value)
		{
			value += _value.value;
			return *this;
		}

		JsonString operator +(const JsonString& _value)const
		{
			JsonString res = value;
			res += _value;
			return res;
		}

		JsonString& operator =(const std::basic_string<CharaType>& _value)
		{
			if (&value == &_value)return *this;
			value = _value;
			return *this;
		}

		JsonString& operator +=(const std::basic_string<CharaType>& _value)
		{
			value += value;
			return *this;
		}

		JsonString operator +(const std::basic_string<CharaType>& _value)const
		{
			JsonString res = value;
			res += _value;
			return res;
		}
	public://To BaseClass Operator Functions//

		Ch_Json_BaseTypeMethods(CH_Json_String_Operator_Functions);

	public://To String Operator Functions//

		operator std::basic_string<CharaType>()const
		{
			return GetString();
		}

	public://Constructor Destructor//

		JsonString();

		JsonString(const JsonString& _str);

		JsonString(const std::basic_string<CharaType>& _str);

		Ch_Json_BaseTypeMethods(CH_Json_String_Constructor_Functions);

	public:

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void SetString(const std::basic_string<CharaType>& _text)
		{
			value = _text;
		}

	public:

		std::basic_string<CharaType> GetRawData()const override;

		std::basic_string<CharaType> GetString()const
		{
			return value;
		}


	private:

		bool IsCutChar(CharaType _char)const
		{
			return _char == ChStd::GetSGQuotation<CharaType>()[0] ||
				_char == ChStd::GetDBQuotation<CharaType>()[0];
		}

	private:

		bool AddDecimal(std::basic_string<CharaType>& _outText, const std::basic_string<CharaType>& _inText, const std::basic_string<CharaType>& _baseDecimal);

	private:

		std::basic_string<CharaType> value = ChStd::GetZeroChara<CharaType>();
	};

}

#endif