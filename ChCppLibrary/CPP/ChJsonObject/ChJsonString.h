#ifndef Ch_CPP_JsonString_h
#define Ch_CPP_JsonString_h

#include"ChJsonBaseType.h"

#include"../../BasePack/ChStr.h"

#ifndef CH_JSON_STRING_b_CHARA_FUNCTION
#define CH_JSON_STRING_b_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(Get_b_Chara,type)
#endif

#ifndef CH_JSON_STRING_f_CHARA_FUNCTION
#define CH_JSON_STRING_f_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(Get_f_Chara,type)
#endif

#ifndef CH_JSON_STRING_n_CHARA_FUNCTION
#define CH_JSON_STRING_n_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(Get_n_Chara,type)
#endif

#ifndef CH_JSON_STRING_r_CHARA_FUNCTION
#define CH_JSON_STRING_r_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(Get_r_Chara,type)
#endif

#ifndef CH_JSON_STRING_t_CHARA_FUNCTION
#define CH_JSON_STRING_t_CHARA_FUNCTION(type) CH_NUMBER_FUNCTION_BASE(Get_t_Chara,type)
#endif

#ifndef	CH_Json_String_Operator_Functions
#define	CH_Json_String_Operator_Functions(_type)\
JsonString& operator =(const _type##& _value){\
	value->value = ChStr::GetTextFromNum<##_type##, CharaType>(_value);\
	return *this;}
#endif

#ifndef	CH_Json_String_Constructor_Functions
#define	CH_Json_String_Constructor_Functions(_type)\
JsonString(const _type##& _value){\
	CRTInit();\
	*this = ChStr::GetTextFromNum<##_type##, CharaType>(_value);}
#endif

namespace ChCpp
{
	template<typename CharaType>
	class JsonString :public JsonBaseType<CharaType>
	{
	public:

		struct JsonStringCRT
		{
#ifdef CRT
			std::basic_string<CharaType> value = ChStd::GetZeroChara<CharaType>();
#endif
		};

	public://static Create Function//

#ifdef CRT
		static ChPtr::Shared<JsonString> CreateObject(const std::basic_string<CharaType>& _text)
		{
			auto&& res = ChPtr::Make_S<JsonString>();
			*res = _text;
			return res;
		}
#endif
	public://Operator Functions//

#ifdef CRT
		JsonString& operator =(const JsonString& _value)
		{
			if (this == &_value)return *this;
			value->value = _value.value->value;
			return *this;
		}

		JsonString& operator +=(const JsonString& _value)
		{
			value->value += _value.value->value;
			return *this;
		}

		JsonString operator +(const JsonString& _value)const
		{
			JsonString res = value->value;
			res += _value;
			return res;
		}

		JsonString& operator =(const std::basic_string<CharaType>& _value)
		{
			if (&value->value == &_value)return *this;
			value->value = _value;
			return *this;
		}

		JsonString& operator +=(const std::basic_string<CharaType>& _value)
		{
			value->value += value->value;
			return *this;
		}

		JsonString operator +(const std::basic_string<CharaType>& _value)const
		{
			JsonString res = value->value;
			res += _value;
			return res;
		}
#endif
	public://To BaseClass Operator Functions//

#ifdef CRT
		Ch_Json_BaseTypeMethods(CH_Json_String_Operator_Functions);

#endif
	public://To String Operator Functions//

#ifdef CRT
		operator std::basic_string<CharaType>()const
		{
			return GetString();
		}
#endif
	public://Constructor Destructor//

#ifdef CRT
		JsonString();

		JsonString(const JsonString& _str);

		JsonString(const std::basic_string<CharaType>& _str);

		Ch_Json_BaseTypeMethods(CH_Json_String_Constructor_Functions);
#endif
		virtual ~JsonString()
		{
			CRTRelease();
		}

	private:

		void CRTInit();

		void CRTRelease();

	public:

#ifdef CRT
		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		void SetString(const std::basic_string<CharaType>& _text)
		{
			value->value = _text;
		}
#endif

	public:

#ifdef CRT
		std::basic_string<CharaType> GetRawData()const override;

		std::basic_string<CharaType> GetString()const
		{
			return value->value;
		}
#endif
	private:

#ifdef CRT
		bool IsCutChar(CharaType _char)const
		{
			return _char == ChStd::GetSGQuotation<CharaType>()[0] ||
				_char == ChStd::GetDBQuotation<CharaType>()[0];
		}
#endif
	private:

#ifdef CRT
		bool AddDecimal(std::basic_string<CharaType>& _outText,const std::basic_string<CharaType>& _inText, const std::basic_string<CharaType>& _baseDecimal);
#endif
	private:

		JsonStringCRT* value = nullptr;
	};

}

#ifdef CRT

namespace ChCpp
{
	namespace Json
	{
		CH_TO_NUMBER_FUNCTION(CH_JSON_STRING_b_CHARA_FUNCTION, "b");

		CH_TO_NUMBER_FUNCTION(CH_JSON_STRING_f_CHARA_FUNCTION, "f");

		CH_TO_NUMBER_FUNCTION(CH_JSON_STRING_n_CHARA_FUNCTION, "n");

		CH_TO_NUMBER_FUNCTION(CH_JSON_STRING_r_CHARA_FUNCTION, "r");

		CH_TO_NUMBER_FUNCTION(CH_JSON_STRING_t_CHARA_FUNCTION, "t");


		static constexpr unsigned char ESCAPE_SEQUENCE_COUNT = 7;

		template<typename CharaType>
		static const std::vector<CharaType> EscapeSequenceBaseCharaList()
		{
			static std::vector<CharaType> res;
			if (!res.empty())return res;

			res.push_back(ChStd::GetSGQuotation<CharaType>()[0]);
			res.push_back(ChStd::GetDBQuotation<CharaType>()[0]);
			res.push_back(ChStd::GetYenChara<CharaType>()[0]);
			res.push_back(ChStd::GetBackChara<CharaType>()[0]);
			res.push_back(ChStd::GetNextPageChara<CharaType>()[0]);
			res.push_back(ChStd::GetLFChara<CharaType>()[0]);
			res.push_back(ChStd::GetCRChara<CharaType>()[0]);
			res.push_back(ChStd::GetTabChara<CharaType>()[0]);

			return res;
		}

		template<typename CharaType>
		static const std::vector<CharaType> EscapeSequenceTextCharaList()
		{
			static std::vector<CharaType> res;
			if (!res.empty())return res;

			res.push_back(ChStd::GetSGQuotation<CharaType>()[0]);
			res.push_back(ChStd::GetDBQuotation<CharaType>()[0]);
			res.push_back(ChStd::GetYenChara<CharaType>()[0]);
			res.push_back(Get_b_Chara<CharaType>()[0]);
			res.push_back(Get_f_Chara<CharaType>()[0]);
			res.push_back(Get_n_Chara<CharaType>()[0]);
			res.push_back(Get_r_Chara<CharaType>()[0]);
			res.push_back(Get_t_Chara<CharaType>()[0]);

			return res;
		}
	}
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonString<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToString(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonString<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString()
{
	CRTInit();
	value->value = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString(const JsonString& _str)
{
	CRTInit();
	value->value = _str.value->value;
}

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString(const std::basic_string<CharaType>& _str)
{
	CRTInit();
	auto&& res = ChPtr::Make_S<JsonString>();
	*res = _str;
	return res;
}

template<typename CharaType>
void ChCpp::JsonString<CharaType>::CRTInit()
{
	value = new JsonStringCRT();
}

template<typename CharaType>
void ChCpp::JsonString<CharaType>::CRTRelease()
{
	delete value;
}

template<typename CharaType>
bool ChCpp::JsonString<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (_jsonText.size() < 2)return false;

	auto textStartChar = _jsonText[0];
	if (!IsCutChar(textStartChar))return false;
	if (_jsonText[_jsonText.size() - 1] != textStartChar)return false;

	std::basic_string<CharaType> testText = _jsonText.substr(1, _jsonText.size() - 2);

	std::basic_string<CharaType> setTestText = ChStd::GetZeroChara<CharaType>();

	auto&& escapeSequenceTextCharaList = Json::EscapeSequenceTextCharaList<CharaType>();
	auto&& escapeSequenceBaseCharaList = Json::EscapeSequenceBaseCharaList<CharaType>();

	bool isEscapeSequence = false;
	for (unsigned long i = 0; i < testText.size(); i++)
	{

		if (testText[i] == ChStd::GetLFChara<CharaType>()[0])
			return false;

		if (testText[i] == ChStd::GetYenChara<CharaType>()[0])
		{
			isEscapeSequence = false;
			for (unsigned long j = 0; j < Json::ESCAPE_SEQUENCE_COUNT; j++)
			{
				if (testText[i + 1] != escapeSequenceTextCharaList[j])continue;
				i++;
				setTestText += escapeSequenceBaseCharaList[j];
				isEscapeSequence = true;
				break;
			}

			if (!isEscapeSequence)
				return false;

			continue;
		}
		setTestText += testText[i];
	}

	value->value = setTestText;

	return true;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonString<CharaType>::GetRawData()const
{
	std::basic_string<CharaType> outText = ChStd::GetZeroChara<CharaType>();

	bool isEscapeSequence = false;

	auto&& escapeSequenceTextCharaList = Json::EscapeSequenceTextCharaList<CharaType>();
	auto&& escapeSequenceBaseCharaList = Json::EscapeSequenceBaseCharaList<CharaType>();

	for (unsigned long i = 0; i < value->value.size(); i++)
	{
		isEscapeSequence = false;

		for (unsigned char j = 0; j < Json::ESCAPE_SEQUENCE_COUNT; j++)
		{
			if (escapeSequenceBaseCharaList[j] != value->value[i])continue;
			outText += ChStd::GetYenChara<CharaType>();
			outText += escapeSequenceTextCharaList[j];
			isEscapeSequence = true;
			break;
		}
		if (isEscapeSequence)continue;

		outText += value->value[i];
	}

	return ChStd::GetDBQuotation<CharaType>() + outText + ChStd::GetDBQuotation<CharaType>();
}

template<typename CharaType>
bool ChCpp::JsonString<CharaType>::AddDecimal(std::basic_string<CharaType>& _outText, const std::basic_string<CharaType>& _inText, const std::basic_string<CharaType>& _baseDecimal)
{
	if (!ChStd::IsBaseNumbers(_inText, _baseDecimal))return false;

	_outText += ChStd::ToBaseNumber(_inText, _baseDecimal, ChStd::DECIMAL_NUMBUR<CharaType>());

	return true;
}

#endif

#include"SharedFunctions/ChJsonSharedArrayBooleanNumberString.h"


#endif