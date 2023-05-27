#ifndef Ch_CPP_JsonNumber_h
#define Ch_CPP_JsonNumber_h

#include"ChJsonBaseType.h"

namespace ChCpp
{

	class JsonNumber :public JsonBaseType
	{
	public://Operator Functions//


		JsonNumber& operator= (const JsonNumber& _val);

		JsonNumber& operator = (const JsonNumber& _val);
		JsonNumber& operator += (const JsonNumber& _val);
		JsonNumber operator + (const JsonNumber& _val)const;
		JsonNumber& operator -= (const JsonNumber& _val);
		JsonNumber operator - (const JsonNumber& _val)const;
		JsonNumber& operator *= (const JsonNumber& _val);
		JsonNumber operator * (const JsonNumber& _val)const;
		JsonNumber& operator /= (const JsonNumber& _val);
		JsonNumber operator / (const JsonNumber& _val)const;
		JsonNumber& operator %= (const JsonNumber& _val);
		JsonNumber operator % (const JsonNumber& _val)const;

	public://To BaseClass Operator Functions//

		template<typename BaseType>
		operator BaseType()const;

		template<typename BaseType>
		JsonNumber operator = (const BaseType& _base);


	public://To String Operator Functions//

		operator JsonString()const;
		operator std::string()const;

	public://Constructor Destructor//

		JsonNumber();

		JsonNumber(const JsonNumber& _val);

		template<typename BaseType>
		JsonNumber(const BaseType& _val);

	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		long double value;
	};

	//テンプレートの明示化//
	//(Template Explicit)//
	template JsonNumber::operator char()const;
	template JsonNumber::operator short()const;
	template JsonNumber::operator int()const;
	template JsonNumber::operator long()const;
	template JsonNumber::operator long long()const;
	template JsonNumber::operator unsigned char()const;
	template JsonNumber::operator unsigned short()const;
	template JsonNumber::operator unsigned int()const;
	template JsonNumber::operator unsigned long()const;
	template JsonNumber::operator unsigned long long()const;
	template JsonNumber::operator float()const;
	template JsonNumber::operator double()const;
	template JsonNumber::operator long double()const;

	template JsonNumber JsonNumber::operator = (const char& _base);
	template JsonNumber JsonNumber::operator = (const short& _base);
	template JsonNumber JsonNumber::operator = (const int& _base);
	template JsonNumber JsonNumber::operator = (const long& _base);
	template JsonNumber JsonNumber::operator = (const long long& _base);
	template JsonNumber JsonNumber::operator = (const unsigned char& _base);
	template JsonNumber JsonNumber::operator = (const unsigned short& _base);
	template JsonNumber JsonNumber::operator = (const unsigned int& _base);
	template JsonNumber JsonNumber::operator = (const unsigned long& _base);
	template JsonNumber JsonNumber::operator = (const unsigned long long& _base);
	template JsonNumber JsonNumber::operator = (const float& _base);
	template JsonNumber JsonNumber::operator = (const double& _base);
	template JsonNumber JsonNumber::operator = (const long double& _base);

	template JsonNumber::JsonNumber(const char& _base);
	template JsonNumber::JsonNumber(const short& _base);
	template JsonNumber::JsonNumber(const int& _base);
	template JsonNumber::JsonNumber(const long& _base);
	template JsonNumber::JsonNumber(const long long& _base);
	template JsonNumber::JsonNumber(const unsigned char& _base);
	template JsonNumber::JsonNumber(const unsigned short& _base);
	template JsonNumber::JsonNumber(const unsigned int& _base);
	template JsonNumber::JsonNumber(const unsigned long& _base);
	template JsonNumber::JsonNumber(const unsigned long long& _base);
	template JsonNumber::JsonNumber(const float& _base);
	template JsonNumber::JsonNumber(const double& _base);
	template JsonNumber::JsonNumber(const long double& _base);
}

#endif