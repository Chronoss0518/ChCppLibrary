#ifndef Ch_CPP_JsonBoolean_h
#define Ch_CPP_JsonBoolean_h

#include"ChJsonBaseType.h"

#ifndef CH_JSON_TRUE_TEXT_FUNCTION
#define CH_JSON_TRUE_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION(GetTrueText,type)
#endif

#ifndef CH_JSON_FALSE_TEXT_FUNCTION
#define CH_JSON_FALSE_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION(GetFalseText,type)
#endif

namespace ChCpp
{
	namespace Json
	{
		CH_NUMBER_FUNCTION_BASE(GetTrueText);
		
		CH_NUMBER_FUNCTION_BASE(GetFalseText);
	}

	template<typename CharaType>
	class JsonBoolean :public JsonBaseType<CharaType>
	{
	public://static Create Function//

		static ChPtr::Shared<JsonBoolean> CreateObject(const bool& _flg);

	public://Operator Functions//

		JsonBoolean& operator = (const JsonBoolean& _val);

		JsonBoolean& operator = (const bool& _flg);

	public://To BaseClass Operator Functions//

		operator bool()const;

	public://To String Operator Functions//

		operator std::basic_string<CharaType>()const;

	public://Constructor Destructor//

		JsonBoolean();

		JsonBoolean(const JsonBoolean& _val);

		JsonBoolean(const bool& _val);

	public:

		bool SetRawData(const std::basic_string<CharaType>& _jsonText)override;

		inline void SetFlg(bool _flg) { value = _flg; }

	public:

		std::basic_string<CharaType> GetRawData()const override;

	public:

		bool IsFlg() { return value; }

	private:

		bool value;
	};

}

#endif