#ifndef Ch_CPP_JsonString_h
#define Ch_CPP_JsonString_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonString :public JsonBaseType
	{
	public://Operator Functions//

		JsonString& operator =(const JsonString& _value);

		JsonString& operator +=(const JsonString& _value);

		JsonString& operator +(const JsonString& _value)const;

		JsonString& operator =(const std::string& _value);

		JsonString& operator +=(const std::string& _value);

		JsonString& operator +(const std::string& _value)const;

	public://To BaseClass Operator Functions//

		template<typename BaseType>
		JsonString& operator =(const BaseType& _value);

	public://To String Operator Functions//

		operator std::string()const;

	public://Constructor Destructor//

		JsonString();

		JsonString(const JsonString& _str);

		JsonString(const std::string& _str);

		JsonString(const JsonNumber& _number);

		template<typename BaseType>
		JsonString(const BaseType& _num);

	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		std::string value;
	};


	class JsonBoolean :public JsonBaseType
	{
	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		bool value;
	};
	
	template JsonString& JsonString::operator =(const char& _value);
	template JsonString& JsonString::operator =(const short& _value);
	template JsonString& JsonString::operator =(const int& _value);
	template JsonString& JsonString::operator =(const long& _value);
	template JsonString& JsonString::operator =(const long long& _value);
	template JsonString& JsonString::operator =(const unsigned char& _value);
	template JsonString& JsonString::operator =(const unsigned short& _value);
	template JsonString& JsonString::operator =(const unsigned int& _value);
	template JsonString& JsonString::operator =(const unsigned long& _value);
	template JsonString& JsonString::operator =(const unsigned long long& _value);
	template JsonString& JsonString::operator =(const float& _value);
	template JsonString& JsonString::operator =(const double& _value);
	template JsonString& JsonString::operator =(const long double& _value);
	template JsonString& JsonString::operator =(const std::string& _value);

	template JsonString::JsonString(const char& _value);
	template JsonString::JsonString(const short& _value);
	template JsonString::JsonString(const int& _value);
	template JsonString::JsonString(const long& _value);
	template JsonString::JsonString(const long long& _value);
	template JsonString::JsonString(const unsigned char& _value);
	template JsonString::JsonString(const unsigned short& _value);
	template JsonString::JsonString(const unsigned int& _value);
	template JsonString::JsonString(const unsigned long& _value);
	template JsonString::JsonString(const unsigned long long& _value);
	template JsonString::JsonString(const float& _value);
	template JsonString::JsonString(const double& _value);
	template JsonString::JsonString(const long double& _value);
	template JsonString::JsonString(const std::string& _value);

}

#endif