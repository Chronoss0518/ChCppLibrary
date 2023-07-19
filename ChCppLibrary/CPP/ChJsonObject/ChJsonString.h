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

		JsonString operator +(const JsonString& _value)const;

		JsonString& operator =(const std::string& _value);

		JsonString& operator +=(const std::string& _value);

		JsonString operator +(const std::string& _value)const;

	public://To BaseClass Operator Functions//

		JsonString& operator =(const char& _value);
		JsonString& operator =(const short& _value);
		JsonString& operator =(const int& _value);
		JsonString& operator =(const long& _value);
		JsonString& operator =(const long long& _value);
		JsonString& operator =(const unsigned char& _value);
		JsonString& operator =(const unsigned short& _value);
		JsonString& operator =(const unsigned int& _value);
		JsonString& operator =(const unsigned long& _value);
		JsonString& operator =(const unsigned long long& _value);
		JsonString& operator =(const float& _value);
		JsonString& operator =(const double& _value);
		JsonString& operator =(const long double& _value);

	public://To String Operator Functions//

		operator std::string()const;

	public://Constructor Destructor//

		JsonString();

		JsonString(const JsonString& _str);

		JsonString(const std::string& _str);

		JsonString(const JsonNumber& _number);

		JsonString(const char& _value);
		JsonString(const short& _value);
		JsonString(const int& _value);
		JsonString(const long& _value);
		JsonString(const long long& _value);
		JsonString(const unsigned char& _value);
		JsonString(const unsigned short& _value);
		JsonString(const unsigned int& _value);
		JsonString(const unsigned long& _value);
		JsonString(const unsigned long long& _value);
		JsonString(const float& _value);
		JsonString(const double& _value);
		JsonString(const long double& _value);

	public:

		bool SetRawData(const std::string& _jsonText)override;

		void SetString(const std::string& _text);

	public:

		std::string GetRawData()const override;

		std::string GetString()const;

	private:

		bool IsCutChar(unsigned char _char)const;

	private:

		bool AddDecimal(std::string& _outText,const std::string& _inText, const std::vector<char>& _baseDecimal);

	private:

		std::string value = "";

	};

}

#endif