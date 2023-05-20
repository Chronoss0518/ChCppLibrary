#ifndef Ch_CPP_JsonObject_h
#define Ch_CPP_JsonObject_h

namespace ChCpp
{
	class JsonArray;
	class JsonNumber;
	class JsonString;
	class JsonBoolean;

	class JsonObjectBase
	{
	public://Set Function//

		virtual bool SetRawData(const std::string& _jsonText) = 0;

	public://Get Function//

		virtual std::string GetRawData()const = 0;

	protected://Is Function//

		bool IsObject(const std::string& _json);

		bool IsArray(const std::string& _json);

		bool IsString(const std::string& _json);

		bool IsNumber(const std::string& _json);

		bool IsBoolean(const std::string& _json);
	};

	class JsonObject :public JsonObjectBase
	{
	public://Set Function//

		bool SetRawData(const std::string& _jsonText)override;

		void SetArray(const std::string& _parameterName,const JsonArray& _value);

		void SetNumber(const std::string& _parameterName, const JsonNumber& _value);

		void SetString(const std::string& _parameterName,const JsonString& _value);

		bool SetBoolean(const std::string& _parameterName, const JsonBoolean& _value);

		void SetObject(const std::string& _parameterName,const JsonObject& _value);

	public: //Get Function//

		std::string GetRawData()const override;

		JsonArray GetArray(const std::string& _parameterName)const;

		JsonNumber GetNumber(const std::string& _parameterName)const;

		JsonString GetString(const std::string& _parameterName)const;

		JsonBoolean GetBoolean(const std::string& _parameterName)const;
	
		JsonObject GetObject(const std::string& _parameterName)const;

	private:

		std::map<std::string, ChPtr::Shared<JsonObjectBase>> value;

	};

	class JsonArray :public JsonObjectBase
	{
	public:

		bool SetRawData(const std::string& _jsonText)override;

		void SetValue(unsigned long _num, const JsonObject& _value);

	public:

		std::string GetRawData()const override;

		ChPtr::Shared<JsonObjectBase> GetValue(unsigned long _num)const;

	public:

		void AddObject(ChPtr::Shared<JsonObjectBase> _value);

	private:

		std::vector<ChPtr::Shared<JsonObjectBase>>values;

	};

	class JsonNumber :public JsonObjectBase
	{
	public://Operator Functions//


	public://To BaseClass Operator Functions//

		template<typename BaseType>
		operator BaseType()const;

		template<typename BaseType>
		JsonNumber operator = (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator += (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator + (BaseType& _base)const;

		template<typename BaseType>
		JsonNumber operator -= (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator - (BaseType& _base)const;

		template<typename BaseType>
		JsonNumber operator *= (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator * (BaseType& _base)const;

		template<typename BaseType>
		JsonNumber operator /= (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator / (BaseType& _base)const;

		template<typename BaseType>
		JsonNumber operator %= (BaseType& _base);

		template<typename BaseType>
		JsonNumber operator % (BaseType& _base)const;


	public://To String Operator Functions//

		operator JsonString()const;
		operator std::string()const;

		std::string operator +(JsonNumber& _value)const;


	public://Constructor Destructor//

		JsonNumber();

		template<typename BaseType>
		JsonNumber(BaseType);

	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		long double value;
	};

	class JsonString :public JsonObjectBase
	{
	public:

		JsonString operator +(JsonNumber& _value)const;

	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		std::string value;
	};

	class JsonBoolean :public JsonObjectBase
	{
	public:

		bool SetRawData(const std::string& _jsonText)override;

	public:

		std::string GetRawData()const override;

	private:

		bool value;
	};
}



#endif
