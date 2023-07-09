#ifndef Ch_CPP_JsonBoolean_h
#define Ch_CPP_JsonBoolean_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonBoolean :public JsonBaseType
	{
	public://Operator Functions//

		JsonBoolean& operator = (const JsonBoolean& _val);

		JsonBoolean& operator = (const bool& _flg);

	public://To BaseClass Operator Functions//

		operator bool()const;

	public://To String Operator Functions//

		operator JsonString()const;

	public://Constructor Destructor//

		JsonBoolean();

		JsonBoolean(const JsonBoolean& _val);

		JsonBoolean(const bool& _val);

	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		bool value;
	};

}

#endif