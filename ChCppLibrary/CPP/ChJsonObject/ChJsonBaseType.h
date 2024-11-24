#ifndef Ch_CPP_JsonBaseType_h
#define Ch_CPP_JsonBaseType_h

#ifndef CH_JSON_USE_COLON_FLG
#define CH_JSON_USE_COLON_FLG 0
#endif

#include<string>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"../ChTextObject/ChTextObject.h"
#include"../ChCumulative/ChCumulative.h"

#ifndef Ch_Json_BaseTypeMethods
#define Ch_Json_BaseTypeMethods(_functionDefine)\
_functionDefine(signed char)\
_functionDefine(signed short)\
_functionDefine(signed int)\
_functionDefine(signed long)\
_functionDefine(signed long long)\
_functionDefine(unsigned char)\
_functionDefine(unsigned short)\
_functionDefine(unsigned int)\
_functionDefine(unsigned long)\
_functionDefine(unsigned long long)\
_functionDefine(float)\
_functionDefine(double)\
_functionDefine(long double)
#endif

namespace ChCpp
{
	namespace Json
	{
		CH_NUMBER_FUNCTION_BASE(GetNullText);
	}

	template<typename CharaType>
	class JsonArray;
	
	template<typename CharaType>
	class JsonNumber;
	
	template<typename CharaType>
	class JsonString;
	
	template<typename CharaType>
	class JsonBoolean;
	
	template<typename CharaType>
	class JsonNull;

	template<typename CharaType>
	class JsonObject;
	
	template<typename CharaType>
	class JsonBaseType
	{
	public:

		static ChPtr::Shared<JsonBaseType<CharaType>> GetParameter(const std::basic_string<CharaType>& _json);

		static std::basic_string<CharaType> FormatDocument(const std::basic_string<CharaType>& _str);

	private:

		static ChPtr::Shared<JsonObject<CharaType>> GetParameterToObject(const std::basic_string<CharaType>& _json);

		static ChPtr::Shared<JsonArray<CharaType>> GetParameterToArray(const std::basic_string<CharaType>& _json);

		static ChPtr::Shared<JsonString<CharaType>> GetParameterToString(const std::basic_string<CharaType>& _json);

		static ChPtr::Shared<JsonBoolean<CharaType>> GetParameterToBoolean(const std::basic_string<CharaType>& _json);

		static ChPtr::Shared<JsonNumber<CharaType>> GetParameterToNumber(const std::basic_string<CharaType>& _json);

		static std::basic_string<CharaType> GetTabText(unsigned long _count);

	public://Set Function//

		virtual bool SetRawData(const std::basic_string<CharaType>& _jsonText) = 0;

	public://Get Function//

		virtual std::basic_string<CharaType> GetRawData()const = 0;

	protected:

		std::basic_string<CharaType> GetRawText(unsigned long& _textPosition, const std::basic_string<CharaType>& _parameterObjectText, const TextObject<CharaType>& _parameterObject, bool _jsonObjectFlg);

		std::basic_string<CharaType> GetExtractString(const std::basic_string<CharaType>& _value);
	};

	template<typename CharaType>
	class JsonNull : public JsonBaseType<CharaType>
	{
	public:

	public://Set Function//

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override { return true; };

	public://Get Function//

		std::basic_string<CharaType> GetRawData()const override;
	};
}

#endif